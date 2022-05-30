//
// Created by Yoyotao on 2022/5/26.
//

#include "emissive.h"

Vector3 Emissive::BSDF(const Ray &in_ray, const Ray &out_ray, const Vector3 &n) {
    return {1.f, 1.f, 1.f};
}

bool Emissive::IsScattered() const {
    return false;
}
