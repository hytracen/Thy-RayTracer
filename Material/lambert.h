//
// Created by Yoyotao on 2022/5/26.
//

#ifndef RAYTRACER_LAMBERT_H
#define RAYTRACER_LAMBERT_H

#include "material.h"
#include "../hit_rec.h"

class Lambert : public Material{
public:
    //todo:简化构造函数，可以直接通过Vector3进行初始化
    explicit Lambert(std::shared_ptr<Texture> texture) : Material(texture) {}

    Vector3 BSDF(const Ray &in_ray, const Ray &out_ray, const Vector3 &n) override;

    bool IsScattered() const override;
};


#endif //RAYTRACER_LAMBERT_H
