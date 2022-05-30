//
// Created by Yoyotao on 2022/5/26.
//

#ifndef RAYTRACER_HIT_REC_H
#define RAYTRACER_HIT_REC_H

#include "Utils/vector3.h"
#include "ray.h"

struct HitRec {
    bool is_hit{};
    Vector3 hit_pos;
    Vector3 color;
    Vector3 normal;
};

#endif //RAYTRACER_HIT_REC_H
