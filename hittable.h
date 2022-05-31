//
// Created by Yoyotao on 2022/5/5.
//

#ifndef RAYTRACER_HITTABLE_H
#define RAYTRACER_HITTABLE_H

#include <memory>

#include "Material/material.h"

class Hittable {
public:
    virtual bool Hit(const Ray &in_ray, HitRec& hit_rec) = 0;
    virtual Vector3 GetNormalAt(const Ray &in_ray, const Vector3 &point) = 0;

public:
    std::shared_ptr<Material> mat_;
    bool is_2sided_ = true; // 该几何体是否为双面
};


#endif //RAYTRACER_HITTABLE_H
