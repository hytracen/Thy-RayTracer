//
// Created by Yoyotao on 2022/6/5.
//

#include "bvh_tree.h"

auto CmpX = [](Triangle *t1, Triangle *t2) { return t1->barycenter_.GetX() < t2->barycenter_.GetX(); };
auto CmpY = [](Triangle *t1, Triangle *t2) { return t1->barycenter_.GetY() < t2->barycenter_.GetY(); };
auto CmpZ = [](Triangle *t1, Triangle *t2) { return t1->barycenter_.GetZ() < t2->barycenter_.GetZ(); };

BvhNode *BvhTree::BuildBvh(std::vector<Triangle *> world_tri_list, int l, int r) {
    if (l > r) return nullptr;

    auto *bvh_node = new BvhNode();
    bvh_node->aabb = new Aabb({FLT_MAX, FLT_MAX, FLT_MAX}, {FLT_MIN, FLT_MIN, FLT_MIN});

    for (int i = l; i <= r; ++i) {
        Triangle* tri = world_tri_list.at(i);
        float x_min = std::min(tri->vertexes_.at(0).GetX(),
                               std::min(tri->vertexes_.at(1).GetX(), tri->vertexes_.at(2).GetX()));
        float y_min = std::min(tri->vertexes_.at(0).GetY(),
                               std::min(tri->vertexes_.at(1).GetY(), tri->vertexes_.at(2).GetY()));
        float z_min = std::min(tri->vertexes_.at(0).GetZ(),
                               std::min(tri->vertexes_.at(1).GetZ(), tri->vertexes_.at(2).GetZ()));

        float x_max = std::max(tri->vertexes_.at(0).GetX(),
                               std::max(tri->vertexes_.at(1).GetX(), tri->vertexes_.at(2).GetX()));
        float y_max = std::max(tri->vertexes_.at(0).GetY(),
                               std::max(tri->vertexes_.at(1).GetY(), tri->vertexes_.at(2).GetY()));
        float z_max = std::max(tri->vertexes_.at(0).GetZ(),
                               std::max(tri->vertexes_.at(1).GetZ(), tri->vertexes_.at(2).GetZ()));

        bvh_node->aabb->p_min_.SetX(std::min(x_min, bvh_node->aabb->p_min_.GetX()));
        bvh_node->aabb->p_min_.SetY(std::min(y_min, bvh_node->aabb->p_min_.GetY()));
        bvh_node->aabb->p_min_.SetZ(std::min(z_min, bvh_node->aabb->p_min_.GetZ()));

        bvh_node->aabb->p_max_.SetX(std::max(x_max, bvh_node->aabb->p_max_.GetX()));
        bvh_node->aabb->p_max_.SetY(std::max(y_max, bvh_node->aabb->p_max_.GetY()));
        bvh_node->aabb->p_max_.SetZ(std::max(z_max, bvh_node->aabb->p_max_.GetZ()));
    }

    // 如果当前节点包围盒中的三角形数小于给定值，则作为叶子节点返回
    if (r - l + 1 <= leaf_tri_num_) {
        bvh_node->hittable_list.assign(world_tri_list.begin() + l, world_tri_list.begin() + r + 1);
        return bvh_node;
    }

    // 找出最长的轴，并基于该轴进行排序
    float len_x = bvh_node->aabb->p_max_.GetX() - bvh_node->aabb->p_min_.GetX();
    float len_y = bvh_node->aabb->p_max_.GetY() - bvh_node->aabb->p_min_.GetY();
    float len_z = bvh_node->aabb->p_max_.GetZ() - bvh_node->aabb->p_min_.GetZ();

    if (len_x >= len_y && len_x >= len_z)
        std::sort(world_tri_list.begin() + l, world_tri_list.begin() + r + 1, CmpX);
    if (len_y >= len_x && len_y >= len_z)
        std::sort(world_tri_list.begin() + l, world_tri_list.begin() + r + 1, CmpY);
    if (len_z >= len_x && len_z >= len_y)
        std::sort(world_tri_list.begin() + l, world_tri_list.begin() + r + 1, CmpZ);

    bvh_node->left = BuildBvh(world_tri_list, l, (l + r) / 2);
    bvh_node->right = BuildBvh(world_tri_list, (l + r) / 2 + 1, r);

    return bvh_node;
}

HitRec BvhTree::Hit(const Ray &in_ray) {
    return HitBvh(in_ray, root_);
}

HitRec BvhTree::HitBvh(const Ray &in_ray, BvhNode* root) {
    HitRec hit_rec;

    if (root == nullptr || !CastRay(in_ray, hit_rec, {root->aabb})) return {};

    // 是叶子节点
    if (!root->hittable_list.empty()) {
        if (CastRay(in_ray, hit_rec, root->hittable_list)) {
            return hit_rec;
        } else {
            return {};
        }
    }

    HitRec l_hit_rec = HitBvh(in_ray, root->left);
    HitRec r_hit_rec = HitBvh(in_ray, root->right);

    return (l_hit_rec.ray_t < r_hit_rec.ray_t) ? l_hit_rec : r_hit_rec;
}
