//
// Created by Yoyotao on 2022/5/26.
//

#include "metal.h"

/**
 * @brief 金属应发生镜面反射，当入射角和出射角相等时，BSDF值为1，否则为0
 * @param in_ray
 * @param out_ray
 * @param n
 * @return BSDF值
 */
Vector3 Metal::BSDF(const Ray &in_ray, const Ray &out_ray, const Vector3 &n) {
//    if (fabsf(CosThetaOf2Vec(-in_ray.GetDir(), n) - CosThetaOf2Vec(out_ray.GetDir(), n)) <= 0.01f
//        && (fabsf(CosThetaOf2Vec(n, -in_ray.GetDir()) - fabsf(CosThetaOf2Vec(out_ray.GetDir(),n))) <= 0.01f)) { // 注意in_ray的方向
//        return 1.f;
//    } else {
//        return 0.f;
//    }
    return {0.8f, 0.3f, 0.3f};
}

bool Metal::IsScattered() const {
    return true;
}
