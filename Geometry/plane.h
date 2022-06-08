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
    Plane(std::array<Vector3, 4> vertexes, Vector3 normal, std::shared_ptr<Material> material,
          HittableAttrib hittable_attrib = HittableAttrib()) : vertexes_(vertexes),
                                            normal_(normal) {
        mat_ = material;
        hittable_attrib_ = hittable_attrib;
    }

    bool Hit(const Ray &in_ray, HitRec &hit_rec) override;

    Vector3 GetNormalAt(const Ray &in_ray, const Vector3 &point) override;

    std::vector<Triangle *> GetTriList() override;

private:
    std::array<Vector3, 4> vertexes_; // 顺时针
    Vector3 normal_;
};


#endif //RAYTRACER_PLANE_H
