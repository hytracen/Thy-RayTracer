//
// Created by Yoyotao on 2022/6/7.
//

#ifndef RAYTRACER_TRI_MESH_H
#define RAYTRACER_TRI_MESH_H

#include <vector>
#include <cassert>

#include "../Geometry/triangle.h"
#include "../Utils/OBJ_Loader.h"
#include "../bvh_tree.h"

class TriMesh : public Hittable {
public:
    TriMesh(const std::string &file_name, std::shared_ptr<Material> mat,
            HittableAttrib hittable_attrib = HittableAttrib());

    bool Hit(const Ray &in_ray, HitRec &hit_rec) override;

    void RotateAround(Vector3 p, Vector3 dir, float angle) override;

    void MoveBy(Vector3 dir, float dis) override;

    std::vector<Triangle *> GetTriList() override;

public:
    Vector3 pivot_; // 轴心点
};


#endif //RAYTRACER_TRI_MESH_H
