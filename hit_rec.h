//
// Created by Yoyotao on 2022/5/26.
//

#ifndef RAYTRACER_HIT_REC_H
#define RAYTRACER_HIT_REC_H

#include "Utils/vector3.h"
#include "Utils/numeric.h"
#include "ray.h"

class Hittable;

/**
 * hit_record
 */
struct HitRec {
    bool is_hit = false;
    bool is_front = false; // 是否击中物体的正面（against法线的方向）
    float ray_t = FLT_MAX;
    Vector3 hit_pos;
    Vector3 color;
    Vector3 normal;
    Hittable* hit_object{};
};

#endif //RAYTRACER_HIT_REC_H
