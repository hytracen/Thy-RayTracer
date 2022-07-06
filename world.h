//
// Created by Yoyotao on 2022/5/31.
//

#ifndef RAYTRACER_WORLD_H
#define RAYTRACER_WORLD_H

#include <vector>

#include "hittable.h"
#include "Utils/random_util.h"
#include "Utils/pdf.h"
#include "Utils/constant_value.h"
#include "Geometry/triangle.h"
#include "bvh_tree.h"

class World {
public:
    void Add(Hittable* hittable);

    void BuildBvhTree() {
        bvh_tree_ = new BvhTree(tri_list_, kLeafTriNum);
    }

    Vector3 Shade(const Ray &in_ray, int depth);

    std::vector<Triangle*> GetTriangleList() { return tri_list_; }

private:
    std::vector<Hittable*> hittable_list_;
    std::vector<Hittable*> light_list_;
    std::vector<Triangle*> tri_list_;
    BvhTree* bvh_tree_;
};

#endif //RAYTRACER_WORLD_H
