//
// Created by Yoyotao on 2022/5/30.
//

#include "plane.h"

Plane::~Plane() {
    // 释放内存
    for (auto & triangle : triangles_) {
        delete triangle;
    }
    triangles_.clear();
}

bool Plane::Hit(const Ray &in_ray, HitRec &hit_rec) {
    if (triangles_.at(0)->Hit(in_ray, hit_rec) || triangles_.at(1)->Hit(in_ray, hit_rec)) {
        hit_rec.hit_object = this;
        return true;
    } else {
        return false;
    }
}

Vector3 Plane::GetNormalAt(const Ray &in_ray, const Vector3 &point) {
    return normal_;
}

std::vector<Triangle *> Plane::GetTriList() {
    return triangles_;
}
