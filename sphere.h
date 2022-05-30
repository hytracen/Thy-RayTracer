//
// Created by Yoyotao on 2022/5/5.
//

#ifndef RAYTRACER_SPHERE_H
#define RAYTRACER_SPHERE_H

#include "hittable.h"
#include "Utils/vector3.h"

class Sphere : public Hittable{
public:
    Sphere(Vector3 center, float radius, std::shared_ptr<Material> mat) : center_(center), radius_(radius) {
        mat_ = mat;
    };
    bool Hit(Ray in_ray, HitRec &hit_rec) override;
    Vector3 GetNormalAtPoint(Vector3 point) override;
    Vector3 ColorAtPoint(Vector3 point) override {
        return {0.f, 0.f, 0.f};
    }

private:
    Vector3 center_;
    float radius_;
};


#endif //RAYTRACER_SPHERE_H
