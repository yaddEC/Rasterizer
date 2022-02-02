#include "mathlib.hpp"
#include "math.h"

float Vec3::GetMagnitude()
{
    return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
}

void Vec3::Normalize()
{
    x = x / GetMagnitude();
    y = y / GetMagnitude();
    z = z / GetMagnitude();
}

Vec3 Vec3::operator+(const Vec3 &rhs)
{
    return {this->x + rhs.x, this->y + rhs.y, this->z + rhs.z};
}

Vec3 Vec3::operator*(const float &rhs)
{
    return {this->x * rhs, this->y * rhs, this->z * rhs};
}

Vec4::Vec4(const Vec3 &vec3, float _w )
{
    x = vec3.x;
    y = vec3.y;
    z = vec3.z;
    w = _w;
}

void Vec4::Homogenize()
{
    if (w != 0)
    {
        x = x / w;
        y = y / w;
        z = z / w;
    }
}

float Vec4::GetMagnitude()
{
    Vec4 temp({x, y, z}, w);
    temp.Homogenize();
    return sqrt(pow(temp.x, 2) + pow(temp.y, 2) + pow(temp.z, 2));
}

void Vec4::Normalize()
{
    x = x / GetMagnitude();
    y = y / GetMagnitude();
    z = z / GetMagnitude();
}

Vec4 Vec4::operator+(const Vec4 &rhs)
{
    Vec4 temp({this->x + rhs.x, this->y + rhs.y, this->z + rhs.z}, this->w + rhs.w);
    return temp;
}

Vec4 Vec4::operator*(const float &rhs)
{
    Vec4 temp({this->x * rhs, this->y * rhs, this->z * rhs}, this->w * rhs);
    return temp;
}

Vec4::~Vec4()
{
    
}


Mat4::Mat4(const float(& arr)[16])
{
   for(int i=0; i<16;i++)
   {
       mat[i]=arr[i];
   }
}



