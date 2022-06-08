//
// Created by Yoyotao on 2022/6/5.
//

#ifndef RAYTRACER_AABB_H
#define RAYTRACER_AABB_H

#include "hittable.h"

class Aabb : public Hittable {
public:
    Aabb(Vector3 p_min, Vector3 p_max) : p_min_(p_min), p_max_(p_max) {}
    bool Hit(const Ray &in_ray, HitRec &hit_rec) override;

    Vector3 p_min_, p_max_;
};


#endif //RAYTRACER_AABB_H
