#pragma once
#include "stdio.h"

class Vec3
{
public:
    Vec3();
    Vec3(float a, float b, float c);
    float x;
    float y;
    float z;

    float GetMagnitude();
    void Normalize();
    Vec3 operator+(const Vec3 &rhs);
    Vec3 operator*(const float &rhs);
    ~Vec3();
};

class Vec4
{
public:
    Vec4();
    Vec4(float a, float b, float c, float d);
    float x;
    float y;
    float z;
    float w;
    
    void Print();
    void Homogenize();
    float GetMagnitude();
    void Normalize();
    Vec4 operator+(const Vec4 &rhs);
    Vec4 operator*(const float &rhs);
    Vec4(const Vec3 &vec3, float _w = 1.0f);
    ~Vec4();
};

class Mat4
{
public:
    Mat4();
    float mat[16];
    void Print();
    Mat4(const float (&arr)[16]);
    Vec4 operator*(const Vec4 &rhs);
    Mat4 operator*(const Mat4 &rhs);
    static Mat4 identity();
    static Mat4 CreateTransformMatrix(const Vec3& rotation, const Vec3& position, const Vec3& scale);
    static Mat4 CreateTranslationMatrix(const Vec3 &translation);
    static Mat4 CreateScaleMatrix(const Vec3 &scale);
    static Mat4 CreateXRotationMatrix(float angle);
    static Mat4 CreateYRotationMatrix(float angle);
    static Mat4 CreateZRotationMatrix(float angle);
    void TransposeMatrix(const int M,const int N);

    ~Mat4();
};


