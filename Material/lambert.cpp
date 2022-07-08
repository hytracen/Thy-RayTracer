//
// Created by Yoyotao on 2022/5/26.
//

#include "lambert.h"

Lambert::Lambert(std::shared_ptr<Texture> texture) : Material(texture) {
    material_type_ = MaterialType::kDiffuse;
}

Lambert::Lambert(const Vector3 &albedo) : Material(std::make_shared<ConstantTexture>(albedo)) {
    material_type_ = MaterialType::kDiffuse;
}

/**
 * @brief 郎伯反射的BSDF项
 * @param in_ray
 * @param out_ray
 * @param n
 * @return BSDF值
 */
Vector3 Lambert::BSDF(const Ray &in_ray, const Ray &out_ray, const Vector3 &n) {
    return texture_->AlbedoAtTexel(0.f, 0.f, n) / M_PI;
}

Ray Lambert::Scatter(const Ray &in_ray, const HitRec &hit_rec) {
    Ray scattered_ray;
    scattered_ray.SetOrig(hit_rec.hit_pos);
    scattered_ray.SetDir(LocalToWorld(RandomUtil::SampleCosine(), hit_rec.normal));
    return scattered_ray;
}