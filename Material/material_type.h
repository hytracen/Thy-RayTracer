//
// Created by Yoyotao on 2022/7/6.
//

#ifndef RAYTRACER_MATERIAL_TYPE_H
#define RAYTRACER_MATERIAL_TYPE_H

enum class MaterialType {
    kEmissive,// 自发光
    kDiffuse, // 漫反射
    kSpecular,    // 镜面反射
    kRefractive // 折射
};

#endif //RAYTRACER_MATERIAL_TYPE_H
