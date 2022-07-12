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
        auto * p_u = new Plane{{vertexes_.at(0), vertexes_.at(1), vertexes_.at(2), vertexes_.at(3)},
                  {0.f, 0.f, 1.f}, mat_, hittable_attrib_};
        auto * p_d = new Plane{{vertexes_.at(4), vertexes_.at(5), vertexes_.at(6), vertexes_.at(7)},
                  {0.f,0.f,-1.f}, mat_, hittable_attrib_};
        auto * p_f = new Plane{{vertexes_.at(3), vertexes_.at(2), vertexes_.at(6), vertexes_.at(7)},
                  {1.f,0.f,0.f}, mat_, hittable_attrib_};
        auto * p_b = new Plane{{vertexes_.at(0), vertexes_.at(1), vertexes_.at(5), vertexes_.at(4)},
                  {-1.f,0.f,0.f}, mat_, hittable_attrib_};
        auto * p_l = new Plane{{vertexes_.at(3), vertexes_.at(0), vertexes_.at(4), vertexes_.at(7)},
                  {0.f,-1.f,0.f}, mat_, hittable_attrib_};
        auto * p_r = new Plane{{vertexes_.at(2), vertexes_.at(1), vertexes_.at(5), vertexes_.at(6)},
                  {0.f,1.f,0.f}, mat_, hittable_attrib_};

        planes_.at(0) = p_u;
        planes_.at(1) = p_d;
        planes_.at(2) = p_f;
        planes_.at(3) = p_b;
        planes_.at(4) = p_l;
        planes_.at(5) = p_r;

        for (auto & plane : planes_) {
            auto tmp_tri_list = plane->GetTriList();
            triangles_.insert(triangles_.end(), tmp_tri_list.begin(), tmp_tri_list.end());
        }
    }

    ~Box();
    bool Hit(const Ray &in_ray, HitRec &hit_rec) override;
    Vector3 GetNormalAt(const Ray &in_ray, const Vector3 &point) override;
    std::vector<Triangle *> GetTriList() override;

    void RotateAround(Vector3 p, Vector3 dir, float angle) override;

    void MoveBy(Vector3 dir, float dis) override;

public:
    Vector3 center_; // 中心

private:
    std::array<Vector3, 8> vertexes_; // 顺时针，自上而下初始化
    std::array<Plane*, 6> planes_;
};


#endif //RAYTRACER_BOX_H
