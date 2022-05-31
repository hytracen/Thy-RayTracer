//
// Created by Yoyotao on 2022/5/26.
//

#include "lambert.h"

/**
 * @brief 郎伯反射的BSDF项
 * @param in_ray
 * @param out_ray
 * @param n
 * @return BSDF值
 */
Vector3 Lambert::BSDF(const Ray &in_ray, const Ray &out_ray, const Vector3 &n) {
//    if (fabsf(CosThetaOf2Vec(-in_ray.GetDir(), n) - CosThetaOf2Vec(out_ray.GetDir(), n)) <= 0.01f
//        && (fabsf(CosThetaOf2Vec(n, -in_ray.GetDir()) - fabsf(CosThetaOf2Vec(out_ray.GetDir(),n))) <= 0.01f)) { // 注意in_ray的方向
//        return 1.f;
//    } else {
//        return 0.f;
//    }
    return texture_->AlbedoAtTexel(0.f, 0.f, n) / M_PI;
}

bool Lambert::IsScattered() const {
    return true;
}
