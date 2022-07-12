//
// Created by Yoyotao on 2022/5/31.
//

#include "world.h"
#include "Material/metal.h"

#define BVH
//#define NotBVH

void World::Add(Hittable *hittable) {
    switch (hittable->hittable_attrib_.type_) {
        case HittableType::kLight: {
            auto* light = dynamic_cast<Light *>(hittable);
            if (light)
                light_list_.push_back(light);
            break;
        }
        case HittableType::kNormal:
        case HittableType::kNoTri:
            break;
    }
    std::vector<Triangle*> tri_list = hittable->GetTriList();
    tri_list_.insert(tri_list_.end(), tri_list.begin(), tri_list.end());
    hittable_list_.push_back(hittable);
}

Vector3 World::Shade(const Ray &in_ray, int depth) {
    if (depth <= 0) return {}; // 达到最大递归深度，递归结束

    HitRec hit_rec;
#ifdef NotBVH
    if (CastRay(in_ray, hit_rec, hittable_list_)) {
#endif
#ifdef BVH
        if ((hit_rec = bvh_tree_->Hit(in_ray)).is_hit) {
#endif
        Hittable *hit_obj = hit_rec.hit_object;

        if ((!hit_obj->hittable_attrib_.is_2sided_) && in_ray.GetDir().Dot(hit_rec.normal) > 0.f) // 物体为单面且光线击中物体背面
            return {};

        Vector3 r_dir, r_indir; // 直接光照和间接光照
        Ray scattered_ray = hit_obj->mat_->Scatter(in_ray, hit_rec); // 散射后的光线
        float p = RandomUtil::GetUniformFloat(0.f, 1.f); // Russian Roulette

        switch (hit_obj->mat_->material_type_) {
            case MaterialType::kEmissive: { // 自发光材质（光源）
                return hit_rec.color;
            }

            case MaterialType::kDiffuse: { // 漫反射材质
                // 直接光照计算（直接向光源采样）
                for (auto light: light_list_) {
                    if (!light->hittable_attrib_.is_2sided_ &&
                        hit_rec.normal.Dot(light->GetNormalAt(in_ray, {})) > 0.f)
                        continue;

                    Vector3 s_p = light->SamplePoint();
                    float dis = GetDistanceBetween2Points(s_p, hit_rec.hit_pos);
                    Ray ray2light{hit_rec.hit_pos, (s_p - hit_rec.hit_pos).Normalize()};
                    HitRec light_hit_rec;
#ifdef NotBVH
                    CastRay(ray2light, light_hit_rec, hittable_list_);
#endif
#ifdef BVH
                    light_hit_rec = bvh_tree_->Hit(ray2light);
#endif
                    // 如果中间没有其他物体阻挡
                    if (dis - GetDistanceBetween2Points(hit_rec.hit_pos, light_hit_rec.hit_pos) < 0.01f) {
                        float light_area = 0.f; // 光源面积
                        for (auto tri : light->GetTriList())
                            light_area += tri->GetArea();
                        r_dir += hit_obj->mat_->BSDF(in_ray, ray2light, hit_rec.normal) * Vector3{15.f, 15.f, 15.f}
                                 * ray2light.GetDir().Dot(hit_rec.normal) *
                                 (-ray2light.GetDir()).Dot(light->GetNormalAt(ray2light, {}))
                                 / powf(dis, 2) / Pdf::GetUniAreaPdf(light_area);
                    }
                }

                // 间接光照计算
                if (p < kRR) {
                    r_indir = (scattered_ray.GetDir()).Dot(hit_rec.normal) *
                              hit_obj->mat_->BSDF(in_ray, scattered_ray, hit_rec.normal) *
                              Shade(scattered_ray, depth - 1) /
                              Pdf::GetCosineHemiPdf(scattered_ray.GetDir(), hit_rec.normal) / kRR;
                }
                return r_dir + r_indir;
            }

            case MaterialType::kSpecular:
            case MaterialType::kRefractive:{
                if (p < kRR) {
                    return hit_obj->mat_->BSDF(in_ray, scattered_ray, hit_rec.normal) *
                           Shade(scattered_ray, depth - 1) / kRR;
                } else
                    return r_dir;
            }
        }
    } else {
        return {};
    }
}

bool CastRay(const Ray &in_ray, HitRec &hit_rec, const std::vector<Hittable*>& hittable_list) {
    float t = FLT_MAX;
    bool is_hit = false;
    HitRec temp_hit_rec;
    for (auto hittable: hittable_list) {
        if (hittable->Hit(in_ray, temp_hit_rec)) {
            is_hit = true;
            if (temp_hit_rec.ray_t < t) {
                hit_rec = temp_hit_rec;
                hit_rec.hit_object = hittable;
                t = hit_rec.ray_t;
            }
        }
    }
    return is_hit;
}
