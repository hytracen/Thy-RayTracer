//
// Created by Yoyotao on 2022/5/31.
//

#ifndef RAYTRACER_WORLD_H
#define RAYTRACER_WORLD_H

#include <vector>

#include "hittable.h"
#include "Utils/random_util.h"
#include "Utils/pdf.h"
#include "Utils/constant_value.h"


enum class HittableType {
    kNormal,
    kLight
};

class World {
public:
    void Add(Hittable* hittable, HittableType hittable_type = HittableType::kNormal);
    Vector3 Shade(const Ray &in_ray, int depth);
    bool CastRay(const Ray &in_ray, HitRec &hit_rec);
private:
    std::vector<Hittable*> hittable_list_;
    std::vector<Hittable*> light_list_;
};


#endif //RAYTRACER_WORLD_H
