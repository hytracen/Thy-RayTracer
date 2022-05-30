//
// Created by Yoyotao on 2022/5/26.
//

#ifndef RAYTRACER_METAL_H
#define RAYTRACER_METAL_H

#include "material.h"
#include "../hit_rec.h"

class Metal : public Material{
public:
    Vector3 BSDF(const Ray &in_ray, const Ray &out_ray, const Vector3 &n) override;

    bool IsScattered() const override;
};


#endif //RAYTRACER_METAL_H
