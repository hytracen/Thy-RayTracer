//
// Created by Yoyotao on 2022/5/30.
//

#include "plane.h"

bool Plane::Hit(Ray in_ray, HitRec &hit_rec) {
    Triangle t1{{vertexes_.at(0), vertexes_.at(1), vertexes_.at(2)}, normal_, mat_};
    Triangle t2{{vertexes_.at(0), vertexes_.at(2), vertexes_.at(3)}, normal_, mat_};
    if (t1.Hit(in_ray, hit_rec) || t2.Hit(in_ray, hit_rec)) {
        return true;
    } else {
        return false;
    }
}

Vector3 Plane::GetNormalAtPoint(const Vector3 &point) {
    return normal_;
}
