//
// Created by Yoyotao on 2022/5/31.
//

#include "world.h"

void World::Add(Hittable *hittable, HittableType hittable_type) {
    switch (hittable_type) {
        case HittableType::kLight:
            light_list_.push_back(hittable); // 此处不加break, 确保总是将hittable添加至hittable_list中
        case HittableType::kNormal:
            hittable_list_.push_back(hittable);
            break;
    }
}

Vector3 World::Shade(const Ray &in_ray, int depth) {
    if (depth <= 0) return {}; // 达到最大递归深度，递归结束

    HitRec hit_rec;
    if (CastRay(in_ray, hit_rec)) {
        Hittable* hit_obj = hit_rec.hit_object;

        if ((!hit_obj->is_2sided_) && in_ray.GetDir().Dot(hit_rec.normal) > 0.f) // 物体为单面且光线击中物体背面
            return {};
        if (!hit_obj->mat_->IsScattered()) // 击中光源时，直接返回光源的颜色
            return hit_rec.color;

        // 直接光照计算
        Vector3 r_dir;

        for (auto light: light_list_) {
            if (!light->is_2sided_ && hit_rec.normal.Dot(light->GetNormalAt(in_ray, {})) > 0.f) continue;
            float x = RandomUtil::GetUniformFloat(213.f, 343.f);
            float y = RandomUtil::GetUniformFloat(227.f, 332.f);
            float z = 554.f;
            float dis = GetDistanceBetween2Points({x, y, z}, hit_rec.hit_pos);
            Ray ray2light{hit_rec.hit_pos, (Vector3{x, y, z} - hit_rec.hit_pos).Normalize()};
            HitRec light_hit_rec;
            CastRay(ray2light, light_hit_rec);
            // 如果中间没有其他物体阻挡
            if (dis - GetDistanceBetween2Points(hit_rec.hit_pos, light_hit_rec.hit_pos) < 0.01f) {
                r_dir += hit_obj->mat_->BSDF(in_ray, ray2light, hit_rec.normal) * Vector3{15.f, 15.f, 15.f}
                         * ray2light.GetDir().Dot(hit_rec.normal) *
                         (-ray2light.GetDir()).Dot(light->GetNormalAt(ray2light, {}))
                         / powf(dis, 2) / Pdf::GetUniAreaPdf(13650.f);
            }
        }

        // 间接光照计算
        Vector3 r_indir;
        float p = RandomUtil::GetUniformFloat(0.f, 1.f);
        if (p < kRR) {
            Ray scattered_ray;
            scattered_ray.SetOrig(hit_rec.hit_pos);
            scattered_ray.SetDir(LocalToWorld(RandomUtil::SampleCosine(), hit_rec.normal));
            r_indir = (scattered_ray.GetDir()).Dot(hit_rec.normal) *
                      hit_obj->mat_->BSDF(in_ray, scattered_ray, hit_rec.normal) *
                      Shade(scattered_ray, depth - 1) / Pdf::GetCosineHemiPdf(scattered_ray.GetDir(), hit_rec.normal)/ kRR;
        }
        return r_dir + r_indir;
    } else {
        return {};
    }
}

bool World::CastRay(const Ray &in_ray, HitRec &hit_rec) {
    float t = std::numeric_limits<float>::max();
    bool is_hit = false;
    HitRec temp_hit_rec;
    for (auto hittable: hittable_list_) {
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
