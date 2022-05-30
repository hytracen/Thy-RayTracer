//
// Created by Yoyotao on 2022/5/23.
//

#include "light.h"

bool Light::Hit(Ray in_ray, HitRec &hit_rec) {
    return false;
}

Vector3 Light::GetNormalAtPoint(Vector3 point) {
    return Vector3();
}

Vector3 Light::ColorAtPoint(Vector3 point) {
    return Vector3();
}
