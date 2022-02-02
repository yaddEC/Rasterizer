#pragma once

class Vec3
{
public:
    float x;
    float y;
    float z;

    float GetMagnitude();
    void Normalize();
    Vec3 operator+ ( const Vec3& rhs);
    Vec3 operator* ( const float& rhs);
    
};

class Vec4
{
public:
    float x;
    float y;
    float z;
    float w;

    Vec4(const Vec3& vec3, float _w = 1.0f);
    void Homogenize();
    float GetMagnitude();
    void Normalize();
    Vec4 operator+ ( const Vec4& rhs);
    Vec4 operator* ( const float& rhs);
    ~Vec4();

};

class Mat4
{
public:
    float mat[4][4];
    Mat4();
    void Homogenize();
    void Normalize();
    Mat4 operator* ( const Vec4& rhs);
    Mat4 operator* ( const Mat4& rhs);
    static Mat4 CreateTransformMatrix(const Vec3& rotation, const Vec3& position, const Vec3& scale);

    ~Mat4();

};


