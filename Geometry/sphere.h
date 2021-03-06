

//
// Created by Yoyotao on 2022/5/5.
//

#ifndef RAYTRACER_SPHERE_H
#define RAYTRACER_SPHERE_H

#include "../hittable.h"
#include "../Utils/vector3.h"

class Sphere : public Hittable{
public:
    Sphere(Vector3 center, float radius, std::shared_ptr<Material> mat) : center_(center), radius_(radius) {
        mat_ = mat;
        hittable_attrib_ = HittableAttrib(true, HittableType::kNoTri);
    };
    bool Hit(const Ray &in_ray, HitRec &hit_rec) override;
    Vector3 GetNormalAt(const Ray &in_ray, const Vector3 &point) override;
    std::vector<Triangle *> GetTriList() override;

private:
    Vector3 center_;
    float radius_;
};


#endif //RAYTRACER_SPHERE_H
