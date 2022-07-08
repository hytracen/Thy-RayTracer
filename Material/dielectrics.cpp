//
// Created by Yoyotao on 2022/7/7.
//

#include "dielectrics.h"

Dielectrics::Dielectrics(std::shared_ptr<Texture> texture, float ior) : Material(texture), ior_(ior) {
    material_type_ = MaterialType::kRefractive;
}

Vector3 Dielectrics::BSDF(const Ray &in_ray, const Ray &out_ray, const Vector3 &n) {
    return texture_->AlbedoAtTexel(0.f, 0.f, n);
}

Ray Dielectrics::Scatter(const Ray &in_ray, const HitRec &hit_rec) {
    float cos_i = fminf(-hit_rec.normal.Dot(in_ray.GetDir()), 1.f);
    float sin_i = sqrtf(1 - cos_i * cos_i);
    float eta_ir = hit_rec.is_front ? 1.f / ior_ : ior_; // 外部折射率与内部折射率之比，方便后续计算
    float p = RandomUtil::GetUniformFloat(0, 1);
    if (eta_ir * sin_i > 1.f || p < Reflectance(cos_i, ior_)) { // 只能发生反射或者随机数小于反射率的情况下，进行反射
        return Reflect(in_ray, hit_rec.hit_pos, hit_rec.normal);
    } else {
        return Refract(in_ray, hit_rec, eta_ir);
    }
}

Ray Refract(const Ray &in_ray, const HitRec &hit_rec, float eta_ir) {
    Vector3 in_dir = in_ray.GetDir().Normalize();
    Vector3 n = hit_rec.normal;
//    float delta = 1.f - powf(eta_ir, 2.f) * (1.f - powf(n.Dot(in_dir), 2));
//
//    Ray refracted_ray;
//    refracted_ray.SetOrig(hit_rec.hit_pos);
//    refracted_ray.SetDir(-(eta_ir * n.Dot(in_dir) + sqrtf(delta)) * n + eta_ir * in_dir);

    auto cos_theta = fminf(-in_dir.Dot(n), 1.0);
    Vector3 r_out_perp = eta_ir * (in_dir + cos_theta * n);
    Vector3 r_out_parallel = -sqrtf(fabsf(1.0f - powf(r_out_perp.Length(), 2.f))) * n;

    Ray refracted_ray;
    refracted_ray.SetOrig(hit_rec.hit_pos);
    refracted_ray.SetDir((r_out_perp + r_out_parallel).Normalize());

    return refracted_ray;
}

float Reflectance(float cos_i, float ior) {
    // Schlick Approximation
    float r_0 = powf((1 - ior) / (1 + ior), 2);
    return r_0 + (1 - r_0) * powf((1 - cos_i), 5);
}
