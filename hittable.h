//
// Created by Yoyotao on 2022/5/5.
//

#ifndef RAYTRACER_HITTABLE_H
#define RAYTRACER_HITTABLE_H

#include <memory>

#include "Material/material.h"

class Hittable {
public:
    virtual bool Hit(Ray in_ray, HitRec& hit_rec) = 0;
    virtual Vector3 GetNormalAtPoint(Vector3 point) = 0;
    virtual Vector3 ColorAtPoint(Vector3 point) = 0;

    std::shared_ptr<Material> mat_;
};


#endif //RAYTRACER_HITTABLE_H