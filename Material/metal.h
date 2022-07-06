//
// Created by Yoyotao on 2022/7/6.
//

#ifndef RAYTRACER_METAL_H
#define RAYTRACER_METAL_H

#include "material.h"

/**
 * 金属材质（镜面反射）
 */
class Metal : public Material{
public:
    explicit Metal(std::shared_ptr<Texture> texture);

    Vector3 BSDF(const Ray &in_ray, const Ray &out_ray, const Vector3 &n) override;

    Ray Scatter(const Ray &in_ray, const Vector3 &p, const Vector3 &n) override;

    bool IsScattered() const override;
};


#endif //RAYTRACER_METAL_H
