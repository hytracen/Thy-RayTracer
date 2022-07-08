//
// Created by Yoyotao on 2022/6/7.
//

#include "tri_mesh.h"

TriMesh::TriMesh(const std::string &file_name, std::shared_ptr<Material> mat, HittableAttrib hittable_attrib) {
    mat_ = mat;
    hittable_attrib_ = hittable_attrib;

    objl::Loader loader;
    loader.LoadFile(file_name);

    assert(loader.LoadedMeshes.size() == 1);
    auto mesh = loader.LoadedMeshes[0];

    for (int i = 0; i < mesh.Vertices.size(); i += 3) {
        std::array<Vector3, 3> vertexes;
        for (int j = 0; j < 3; j++) {
            vertexes.at(j) = Vector3{mesh.Vertices[i + j].Position.X,
                              mesh.Vertices[i + j].Position.Y,
                              mesh.Vertices[i + j].Position.Z} * 2000.f + Vector3{200.f, 200.f, 200.f}; // 放大倍数
        }
        triangles_.push_back(new Triangle(vertexes, mat_, hittable_attrib_));
    }
}

bool TriMesh::Hit(const Ray &in_ray, HitRec &hit_rec) {
    // todo: 修改继承结构
//    auto* bvhTree = new BvhTree(tri_list_, 8);
//    hit_rec = bvhTree->Hit(in_ray);
    std::cerr << "TriMesh Hit Error!" << std::endl;
    return hit_rec.is_hit;
}

std::vector<Triangle *> TriMesh::GetTriList() {
    return triangles_;
}

void TriMesh::RotateAround(Vector3 p, Vector3 dir, float angle) {
    // 三角形旋转
    for (auto tri : triangles_) {
        tri->RotateAround(p,dir,angle);
    }
    // todo:轴心旋转
}

void TriMesh::MoveBy(Vector3 dir, float dis) {
    for (auto tri : triangles_) {
        tri->MoveBy(dir, dis);
    }
    // todo : 轴心移动
}
