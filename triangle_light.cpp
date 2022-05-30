//
// Created by Yoyotao on 2022/5/23.
//

#include "triangle_light.h"

bool TriangleLight::Hit(Ray in_ray, HitRec &hit_rec) {
    Vector3 E_1 = vertexes_.at(1) - vertexes_.at(0);
    Vector3 E_2 = vertexes_.at(2) - vertexes_.at(0);
    Vector3 S = in_ray.GetOrig() - vertexes_.at(0);
    Vector3 S_1 = in_ray.GetDir().Cross(E_2);
    Vector3 S_2 = S.Cross(E_1);
    float se_inv = 1.f / S_1.Dot(E_1);
    float t = se_inv * S_2.Dot(E_2);
    float b_1 = se_inv * S_1.Dot(S);
    float b_2 = se_inv * S_2.Dot(in_ray.GetDir());
    if (t >= 0 && (1 - b_1 - b_2) >= 0 && b_1 >=0 && b_2 >= 0) {
//        std::cout << "Hit Light!" << std::endl;
        hit_rec.is_hit = true;
        hit_rec.hit_pos = in_ray.At(t);
        hit_rec.color = ColorAtPoint(hit_rec.hit_pos);
        return true;
    } else {
        hit_rec.is_hit = false;
        return false;
    }
}

Vector3 TriangleLight::ColorAtPoint(Vector3 point) {
    return {2.f, 2.f, 2.f};
}
