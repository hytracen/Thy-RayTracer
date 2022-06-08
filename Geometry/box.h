//
// Created by Yoyotao on 2022/5/30.
//

#ifndef RAYTRACER_BOX_H
#define RAYTRACER_BOX_H

#include "../hittable.h"
#include "plane.h"

class Box : public Hittable {
public:
    // 顶点数组的顺序为顺时针，自上而下
    Box(std::array<Vector3, 8> vertexes, std::shared_ptr<Material> material,
        HittableAttrib hittable_attrib = HittableAttrib())
            : vertexes_(vertexes) {
        mat_ = (material);
        hittable_attrib_ = hittable_attrib;
    }

    bool Hit(const Ray &in_ray, HitRec &hit_rec) override;

    Vector3 GetNormalAt(const Ray &in_ray, const Vector3 &point) override;

private:
    std::array<Vector3, 8> vertexes_; // 顺时针，自上而下初始化
};


#endif //RAYTRACER_BOX_H
