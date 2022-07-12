//
// Created by Yoyotao on 2022/6/5.
//

#ifndef RAYTRACER_BVH_TREE_H
#define RAYTRACER_BVH_TREE_H

#include <vector>

#include "Utils/numeric.h"
#include "Geometry/triangle.h"
#include "aabb.h"

struct BvhNode {
    BvhNode* left = nullptr;
    BvhNode* right = nullptr;
    Aabb* aabb;
    std::vector<Hittable*> hittable_list;
};

class BvhTree {
public:
    BvhTree(const std::vector<Triangle *>& tri_list, int leaf_tri_num) : leaf_tri_num_(leaf_tri_num) {
        root_ = BuildBvh(tri_list, 0, (int)tri_list.size() - 1);
    }

public:
    HitRec Hit(const Ray &in_ray);

private:
    BvhNode* BuildBvh(std::vector<Triangle *> world_tri_list, int l, int r);
    HitRec HitBvh(const Ray &in_ray, BvhNode* root);

private:
    BvhNode* root_;
    int leaf_tri_num_;
};

bool CastRay(const Ray &in_ray, HitRec &hit_rec, const std::vector<Hittable*>& hittable_list);

#endif //RAYTRACER_BVH_TREE_H
