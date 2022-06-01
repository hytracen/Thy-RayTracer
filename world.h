//
// Created by Yoyotao on 2022/5/31.
//

#ifndef RAYTRACER_WORLD_H
#define RAYTRACER_WORLD_H

#include <vector>

#include "hittable.h"
#include "Utils/random_util.h"
#include "Utils/pdf.h"

const float kRR = 0.8f; // 俄罗斯轮盘赌

enum class HittableType {
    kNormal,
    kLight
};

class World {
public:
    void Add(Hittable* hittable, HittableType hittable_type = HittableType::kNormal);
    Vector3 CastRay(const Ray &in_ray, int depth);
private:
    std::vector<Hittable*> hittable_list_;
    std::vector<Hittable*> light_list_;
};


#endif //RAYTRACER_WORLD_H
