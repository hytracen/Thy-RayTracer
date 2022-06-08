//
// Created by Yoyotao on 2022/5/5.
//

#ifndef RAYTRACER_HITTABLE_H
#define RAYTRACER_HITTABLE_H

#include <memory>
#include <vector>

#include "Material/material.h"
#include "hittable_attribute.h"

class Triangle;

// todo: Hittable和Geometry分开
class Hittable {
public:
    virtual bool Hit(const Ray &in_ray, HitRec& hit_rec) = 0;
    virtual Vector3 GetNormalAt(const Ray &in_ray, const Vector3 &point);
    virtual std::vector<Triangle*> GetTriList();

    std::shared_ptr<Material> mat_;
    HittableAttrib hittable_attrib_;
};


#endif //RAYTRACER_HITTABLE_H
