//
// Created by Yoyotao on 2022/7/7.
//

#ifndef RAYTRACER_DIELECTRICS_H
#define RAYTRACER_DIELECTRICS_H

#include "material.h"
#include "metal.h"
#include "../Utils/random_util.h"

class Dielectrics : public Material{
public:
    Dielectrics(std::shared_ptr<Texture> texture, float ior);
    Vector3 BSDF(const Ray &in_ray, const Ray &out_ray, const Vector3 &n) override;
    Ray Scatter(const Ray &in_ray, const HitRec &hit_rec) override;

private:
    float ior_; // 折射率(eta_r / eta_i)
};

/**
 * 计算折射光线的方向
 */
Ray Refract(const Ray &in_ray, const HitRec &hit_rec, float eta_ir);

/**
 * 计算反射比
 */
float Reflectance(float cos_i, float ior);

#endif //RAYTRACER_DIELECTRICS_H
