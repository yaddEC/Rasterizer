#pragma once

class Vec3
{
public:
    float x;
    float y;
    float z;
    Vec3();
    float GetMagnitude();
    void Normalize();
    Vec3 operator+ ( const Vec3& rhs);
    Vec3 operator* ( const float& rhs);
    ~Vec3();
};

class Vec4
{
public:
    float x;
    float y;
    float z;
    float w;
    Vec4();
    Vec4(const Vec3& vec3, float _w = 1.0f);
    void Homogenize();
    void Normalize();
    Vec4 operator+ ( const Vec4& rhs);
    Vec4 operator* ( const float& rhs);
    ~Vec4();

};

