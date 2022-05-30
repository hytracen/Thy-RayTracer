//
// Created by Yoyotao on 2022/5/4.
//

#ifndef RAYTRACER_VECTOR3_H
#define RAYTRACER_VECTOR3_H

#include <cmath>
#include <iostream>

class Vector3 {
public:
    Vector3() : x_(0.f),y_(0.f),z_(0.f){};
    Vector3(float x, float y, float z) : x_(x),y_(y),z_(z){};
    float X() const {return x_;}
    float Y() const {return y_;}
    float Z() const {return z_;}

    Vector3 Normalize() const;
    float Length() const;
    Vector3 Cross(Vector3 v) const;
    float Dot(Vector3 v) const;

    Vector3 operator* (Vector3 v) const {
        return {X() * v.X(), Y() * v.Y(), Z() * v.Z()};
    }

    Vector3& operator+= (Vector3 v) {
        this->x_ += v.X();
        this->y_ += v.Y();
        this->z_ += v.Z();
        return *this;
    }

    Vector3& operator/= (float t) {
        this->x_ /= t;
        this->y_ /= t;
        this->z_ /= t;
        return *this;
    }

private:
    float x_ = 0.f, y_ = 0.f, z_ = 0.f;
};

Vector3 operator+ (Vector3 v1, Vector3 v2);
Vector3 operator* (float t, Vector3 v);
Vector3 operator/ (Vector3 v1, float t);
Vector3 operator- (Vector3 v1, Vector3 v2);
Vector3 operator- (Vector3 v);
std::ostream & operator<<(std::ostream &os, const Vector3 &v);

/**
 * 计算两个向量夹角的余弦值
 * @param v1
 * @param v2
 * @return
 */
float CosThetaOf2Vec(Vector3 v1, Vector3 v2);

// 计算两点间的距离
float GetDistanceBetween2Points (Vector3 v1, Vector3 v2);

/**
 * 将一个向量绕轴旋转给定的角度
 * @param v
 * @param n
 * @param angle
 */
void RotateAroundAxis(Vector3 &v, Vector3 n, float angle);

/**
 * 将Local坐标系（以n为z轴）的向量转换到世界坐标系（以（0，0，1）为z轴）下
 * @param v 待转换的向量
 * @param n 局部坐标系的z轴
 * @return 转换后的向量
 */
Vector3 LocalToWorld(Vector3 v, Vector3 n);

#endif //RAYTRACER_VECTOR3_H
