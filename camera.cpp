//
// Created by Yoyotao on 2022/5/30.
//

#include "camera.h"

Ray Camera::GetRay(const Ray &ray_local) const {
    // 首先将光线的起点平移至标准坐标系下
    Vector3 orig = ray_local.GetOrig() + look_from_;

    // 再进行基底的变换，即旋转操作
    Vector3 local_dir = ray_local.GetDir();
    Vector3 dir = local_dir.X() * u_ + local_dir.Y() * v_ + local_dir.Z() * w_;

    return {orig, dir};
}
