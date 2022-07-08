//
// Created by Yoyotao on 2022/7/6.
//

#include "metal.h"

Metal::Metal(std::shared_ptr<Texture> texture) : Material(texture) {
    material_type_ = MaterialType::kSpecular;
}

Vector3 Metal::BSDF(const Ray &in_ray, const Ray &out_ray, const Vector3 &n) {
    return texture_->AlbedoAtTexel(0.f, 0.f, n);
}

Ray Metal::Scatter(const Ray &in_ray, const HitRec &hit_rec) {
    return Reflect(in_ray, hit_rec.hit_pos, hit_rec.normal);
}

Ray Reflect(const Ray &in_ray, const Vector3 &p, const Vector3 &n) {
    Vector3 in_dir = in_ray.GetDir().Normalize();
    return {p, in_dir - 2 * n * in_dir.Dot(n)};
}
