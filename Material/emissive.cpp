//
// Created by Yoyotao on 2022/5/26.
//

#include "emissive.h"

Emissive::Emissive(std::shared_ptr<Texture> texture) : Material(texture) {
    material_type_ = MaterialType::kEmissive;
}

Vector3 Emissive::BSDF(const Ray &in_ray, const Ray &out_ray, const Vector3 &n) {
    return {1.f, 1.f, 1.f};
}

Ray Emissive::Scatter(const Ray &in_ray, const Vector3 &p, const Vector3 &n) {
    return {};
}

bool Emissive::IsScattered() const {
    return false;
}
