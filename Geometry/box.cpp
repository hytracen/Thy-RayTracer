//
// Created by Yoyotao on 2022/5/30.
//

#include "box.h"

bool Box::Hit(const Ray &in_ray, HitRec &hit_rec) {
    Plane p_u{{vertexes_.at(0), vertexes_.at(1), vertexes_.at(2), vertexes_.at(3)},
              {0.f,0.f,1.f}, mat_, is_2sided_};
    Plane p_d{{vertexes_.at(4), vertexes_.at(5), vertexes_.at(6), vertexes_.at(7)},
              {0.f,0.f,-1.f}, mat_, is_2sided_};
    Plane p_f{{vertexes_.at(3), vertexes_.at(2), vertexes_.at(6), vertexes_.at(7)},
              {1.f,0.f,0.f}, mat_, is_2sided_};
    Plane p_b{{vertexes_.at(0), vertexes_.at(1), vertexes_.at(5), vertexes_.at(4)},
              {-1.f,0.f,0.f}, mat_, is_2sided_};
    Plane p_l{{vertexes_.at(3), vertexes_.at(0), vertexes_.at(4), vertexes_.at(7)},
              {0.f,-1.f,0.f}, mat_, is_2sided_};
    Plane p_r{{vertexes_.at(2), vertexes_.at(1), vertexes_.at(5), vertexes_.at(6)},
              {0.f,1.f,0.f}, mat_, is_2sided_};

    float t = std::numeric_limits<float>::max();
    bool is_hit = false;
    HitRec temp_hit_rec;
    for (auto p: {p_u, p_d, p_f, p_b, p_l, p_r}) {
        if (p.Hit(in_ray, temp_hit_rec)) {
            is_hit = true;
            if (temp_hit_rec.ray_t < t) {
                hit_rec = temp_hit_rec;
                hit_rec.hit_object = this;
                t = hit_rec.ray_t;
            }
        }
    }
    if (t < 0.01f) return false;
    return is_hit;
}

Vector3 Box::GetNormalAt(const Ray &in_ray, const Vector3 &point) {
    // todo:盒体的表面法线
    return {};
}