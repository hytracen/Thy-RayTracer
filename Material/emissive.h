//
// Created by Yoyotao on 2022/5/26.
//

#ifndef RAYTRACER_EMISSIVE_H
#define RAYTRACER_EMISSIVE_H

#include "material.h"

class Emissive : public Material{
public:
    explicit Emissive(std::shared_ptr<Texture> texture);

    Vector3 BSDF(const Ray &in_ray, const Ray &out_ray, const Vector3 &n) override;

    Ray Scatter(const Ray &in_ray, const HitRec &hit_rec) override;
};


#endif //RAYTRACER_EMISSIVE_H
