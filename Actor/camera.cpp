//
// Created by Yoyotao on 2022/5/30.
//

#include "camera.h"

Ray Camera::GetRay(int pixel_idx, int pixel_idy) const {

    float pixel_x =
            ((((float) pixel_idx + RandomUtil::GetUniformFloat(0.f, 1.f)) / (float)width_) * 2 - 1) * aspect_ratio_ *
            (float) std::tan(field_of_view_ * M_PI / 180.f);
    float pixel_y = ((((float) pixel_idy + RandomUtil::GetUniformFloat(0.f, 1.f)) / (float)height_) * 2 - 1) *
                    (float) std::tan(field_of_view_ * M_PI / 180.f);
    float pixel_z = -1.f;

    // 首先将光线的起点平移至标准坐标系下
    Vector3 orig = look_from_;

    // 再进行基底的变换，即旋转操作
    Vector3 local_dir{pixel_x, pixel_y, pixel_z};
    Vector3 dir = local_dir.GetX() * u_ + local_dir.GetY() * v_ + local_dir.GetZ() * w_;

    return {orig, dir};
}
