#include "mathlib.hpp"
#include "math.h"

float Vec3::GetMagnitude()
{
    return sqrt(pow(x,2)+pow(y,2)+pow(z,2));
}

void Vec3::Normalize()
{
    x = x / GetMagnitude();
    y = y / GetMagnitude();
    z = z / GetMagnitude();
}

Vec3 Vec3::operator+ (const Vec3& rhs)
{
    return {this->x+rhs.x,this->y+rhs.y,this->z+rhs.z};
}

Vec3 Vec3::operator* (const float& rhs)
{
    return {this->x*rhs,this->y*rhs,this->z*rhs};
}


