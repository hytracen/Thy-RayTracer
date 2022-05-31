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

Vector3 World::CastRay(const Ray &in_ray, int depth) {
    if (depth <= 0) return {}; // 达到最大递归深度，递归结束

    for (auto *hittable: hittable_list_) {
        HitRec hit_rec;
        if (hittable->Hit(in_ray, hit_rec)) { // 光线击中物体
            if ((!hittable->is_2sided_) && in_ray.GetDir().Dot(hit_rec.normal) > 0.f) // 物体为单面且光线击中物体背面
                return {};
            if (!hittable->mat_->IsScattered()) // 击中光源时，直接返回光源的颜色
                return hit_rec.color;

            // 在光源上随机取点
            Vector3 r_dir;

            for (auto light : light_list_) {
                float x = RandomUtil::GetUniformFloat(213.f, 343.f);
                float y = RandomUtil::GetUniformFloat(227.f, 332.f);
                float z = 554.f;
                float dis = GetDistanceBetween2Points({x, y, z}, hit_rec.hit_pos);
                Ray ray_light{hit_rec.hit_pos, (Vector3{x, y, z} - hit_rec.hit_pos).Normalize()};
                if (light->is_2sided_ || ray_light.GetDir().Dot(light->GetNormalAt(in_ray, {})) < 0.f) {
                    r_dir += hittable->mat_->BSDF(in_ray, ray_light, hit_rec.normal) * Vector3{15.f, 15.f, 15.f}
                            * ray_light.GetDir().Dot(hit_rec.normal) * (-ray_light.GetDir()).Dot(light->GetNormalAt(in_ray, {}))
                            / powf(dis, 2) / Pdf::GetUniAreaVal(13650.f);
                }
            }

            Ray scattered_ray;
            scattered_ray.SetOrig(hit_rec.hit_pos);
            scattered_ray.SetDir(LocalToWorld(RandomUtil::GetRandomPointOnHemisphere(), hit_rec.normal));
            Vector3 r_indir = (scattered_ray.GetDir()).Dot(hit_rec.normal) *
                              hittable->mat_->BSDF(in_ray, scattered_ray, hit_rec.normal) *
                              CastRay(scattered_ray, depth - 1) / Pdf::GetUniHemiVal();

            return r_dir + r_indir;
        }
    }
    return {};
}
