//
// Created by Yoyotao on 2022/5/5.
//

#ifndef RAYTRACER_HITTABLE_H
#define RAYTRACER_HITTABLE_H

#include <memory>
#include <vector>

#include "Material/material.h"
#include "hittable_attribute.h"

class Triangle;

// todo: Hittable和Geometry分开
class Hittable {
public:
    virtual bool Hit(const Ray &in_ray, HitRec& hit_rec) = 0;
    virtual Vector3 GetNormalAt(const Ray &in_ray, const Vector3 &point);
    virtual std::vector<Triangle *> GetTriList();

    // todo: 优化LocalRotate逻辑
    /**
     * 沿自身中轴逆时针旋转
     * @param angle 旋转的角度（角度制）
     */
    virtual void LocalRotate(float angle);

    /**
     * 绕给定轴逆时针旋转
     * @param p 轴的起点
     * @param dir 轴的方向
     * @param angle 角度（角度制）
     */
    virtual void RotateAround(Vector3 p, Vector3 dir, float angle);

    /**
     * 沿着给定的方向移动距离
     * @param dir 方向
     * @param dis 距离
     */
    virtual void MoveBy(Vector3 dir, float dis);

public:
    std::shared_ptr<Material> mat_;
    HittableAttrib hittable_attrib_;

protected:
    std::vector<Triangle*> triangles_; // 三角形面的集合
};


#endif //RAYTRACER_HITTABLE_H
