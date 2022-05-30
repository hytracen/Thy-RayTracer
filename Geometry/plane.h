//
// Created by Yoyotao on 2022/5/30.
//

#ifndef RAYTRACER_PLANE_H
#define RAYTRACER_PLANE_H

#include "../hittable.h"
#include "triangle.h"

class Plane : public Hittable {
public:
    // 顶点数组必须顺时针初始化
    Plane(std::array<Vector3, 4> vertexes, Vector3 normal, std::shared_ptr<Material> material) : vertexes_(vertexes),
                                                                                                 normal_(normal) {
        mat_ = material;
    }

    bool Hit(Ray in_ray, HitRec &hit_rec) override;

    Vector3 GetNormalAtPoint(const Vector3 &point) override;

private:
    std::array<Vector3, 4> vertexes_; // 顺时针
    Vector3 normal_;
};


#endif //RAYTRACER_PLANE_H
