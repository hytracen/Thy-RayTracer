//
// Created by Yoyotao on 2022/5/30.
//

#ifndef RAYTRACER_CAMERA_H
#define RAYTRACER_CAMERA_H

#include "Utils/vector3.h"
#include "ray.h"

class Camera {
public:
    Camera(Vector3 look_from, Vector3 look_at, Vector3 up) : look_from_(look_from), w_(-look_at.Normalize()),
                                                             v_(up), u_(up.Cross(-look_at).Normalize()) {}

    /**
     * 将相机局部坐标系中生成的光线转换到世界坐标系统
     * @param pixel_x
     * @param pixel_y
     * @return 转换后的光线
     */
    Ray GetRay(const Ray &ray_local) const;

private:
    Vector3 look_from_;
    Vector3 u_, v_, w_; // 分别对应x, y, z轴
};


#endif //RAYTRACER_CAMERA_H
