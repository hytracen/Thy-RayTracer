//
// Created by Yoyotao on 2022/5/4.
//

#ifndef RAYTRACER_VECTOR3_H
#define RAYTRACER_VECTOR3_H

#include <cmath>
#include <limits>
#include <iostream>

#include "constant_value.h"

class Vector3 {
public:
    Vector3() : x_(0.f), y_(0.f), z_(0.f) {};

    Vector3(float x, float y, float z) : x_(x), y_(y), z_(z) {};

    float GetX() const { return x_; }

    float GetY() const { return y_; }

    float GetZ() const { return z_; }

    void SetX(float x) { x_ = x; }

    void SetY(float y) { y_ = y; }

    void SetZ(float z) { z_ = z; }

    Vector3 Normalize() const;

    float Length() const;

    Vector3 Inv() const;

    Vector3 Cross(Vector3 v) const;

    float Dot(Vector3 v) const;

    Vector3 operator*(Vector3 v) const {
        return {GetX() * v.GetX(), GetY() * v.GetY(), GetZ() * v.GetZ()};
    }

    Vector3 &operator+=(Vector3 v) {
        this->x_ += v.GetX();
        this->y_ += v.GetY();
        this->z_ += v.GetZ();
        return *this;
    }

    Vector3 &operator/=(float t) {
        this->x_ /= t;
        this->y_ /= t;
        this->z_ /= t;
        return *this;
    }

    /**
     * 将一个点绕轴旋转给定的角度
     * @param p 轴点
     * @param dir 轴的方向
     * @param angle 逆时针旋转的角度
     */
    void PointRotateAroundAxis(const Vector3 &p, const Vector3 &dir, float angle);

    /**
     * 将一个向量绕轴旋转给定的角度
     * @param p 轴点
     * @param dir 轴的方向
     * @param angle 逆时针旋转的角度
     */
    void VectorRotateAroundAxis(const Vector3 &p, const Vector3 &dir, float angle);

private:
    float x_ = 0.f, y_ = 0.f, z_ = 0.f;
};

Vector3 operator+(Vector3 v1, Vector3 v2);

Vector3 operator*(float t, Vector3 v);

Vector3 operator*(Vector3 v, float t);

Vector3 operator/(Vector3 v1, float t);

Vector3 operator-(Vector3 v1, Vector3 v2);

Vector3 operator-(Vector3 v);

std::ostream &operator<<(std::ostream &os, const Vector3 &v);

/**
 * 计算两个向量夹角的余弦值
 * @param v1
 * @param v2
 * @return
 */
float CosThetaOf2Vec(const Vector3 &v1, const Vector3 &v2);

// 计算两点间的距离
float GetDistanceBetween2Points(Vector3 v1, Vector3 v2);

/**
 * 将Local坐标系（以n为z轴）的向量转换到世界坐标系（以（0，0，1）为z轴）下
 * @param v 待转换的向量
 * @param n 局部坐标系的z轴
 * @return 转换后的向量
 */
Vector3 LocalToWorld(Vector3 v, Vector3 n);

/**
 * 判断浮点数是否为0
 */
bool IsNearZero(float f);

#endif //RAYTRACER_VECTOR3_H
