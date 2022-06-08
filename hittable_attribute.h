//
// Created by Hytracen on 2022/6/6.
//

#ifndef RAYTRACER_HITTABLE_ATTRIBUTE_H
#define RAYTRACER_HITTABLE_ATTRIBUTE_H

enum class HittableType {
    kNormal,
    kLight
};

// 属性
struct HittableAttrib {
    explicit HittableAttrib(bool is_2sided = true, HittableType type = HittableType::kNormal) : is_2sided_(is_2sided), type_(type) {}

    bool is_2sided_ = true;
    HittableType type_ = HittableType::kNormal;
};

#endif //RAYTRACER_HITTABLE_ATTRIBUTE_H
