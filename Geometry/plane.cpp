//
// Created by Yoyotao on 2022/5/30.
//

#include "plane.h"

bool Plane::Hit(const Ray &in_ray, HitRec &hit_rec) {
    Triangle t1{{vertexes_.at(0), vertexes_.at(1), vertexes_.at(2)}, normal_, mat_, hittable_attrib_};
    Triangle t2{{vertexes_.at(0), vertexes_.at(2), vertexes_.at(3)}, normal_, mat_, hittable_attrib_};
    if (t1.Hit(in_ray, hit_rec) || t2.Hit(in_ray, hit_rec)) {
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
    return {
            new Triangle{{vertexes_.at(0), vertexes_.at(1), vertexes_.at(2)}, normal_, mat_, hittable_attrib_},
            new Triangle{{vertexes_.at(0), vertexes_.at(2), vertexes_.at(3)}, normal_, mat_, hittable_attrib_}
    };
}
