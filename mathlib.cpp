#include "mathlib.hpp"
#include "math.h"

Vec3::Vec3()
{

}

Vec3::Vec3(float a, float b, float c)
{
    x=a;
    y=b;
    z=c;
}

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

Vec3::~Vec3()
{
    
}

Vec4::Vec4()
{

}

Vec4::Vec4(float a, float b, float c, float d)
{
    x=a;
    y=b;
    z=c;
    w=d;
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
Mat4::Mat4()
{

}

Mat4::Mat4(const float(& arr)[16])
{
   for(int i=0; i<16;i++)
   {
       mat[i]=arr[i];
   }
}

Mat4 Mat4::operator*(const Mat4 &rhs)
{
    Mat4 temp;
    temp.mat[0]=mat[0]*rhs.mat[0]+mat[1]*rhs.mat[4]+mat[2]*rhs.mat[8]+mat[3]*rhs.mat[12];
    temp.mat[1]=mat[0]*rhs.mat[1]+mat[1]*rhs.mat[5]+mat[2]*rhs.mat[9]+mat[3]*rhs.mat[13];
    temp.mat[2]=mat[0]*rhs.mat[2]+mat[1]*rhs.mat[6]+mat[2]*rhs.mat[10]+mat[3]*rhs.mat[14];
    temp.mat[3]=mat[0]*rhs.mat[3]+mat[1]*rhs.mat[7]+mat[2]*rhs.mat[11]+mat[3]*rhs.mat[15];

    temp.mat[4]=mat[4]*rhs.mat[0]+mat[5]*rhs.mat[4]+mat[6]*rhs.mat[8]+mat[7]*rhs.mat[12];
    temp.mat[5]=mat[4]*rhs.mat[1]+mat[5]*rhs.mat[5]+mat[6]*rhs.mat[9]+mat[7]*rhs.mat[13];
    temp.mat[6]=mat[4]*rhs.mat[2]+mat[5]*rhs.mat[6]+mat[6]*rhs.mat[10]+mat[7]*rhs.mat[14];
    temp.mat[7]=mat[4]*rhs.mat[3]+mat[5]*rhs.mat[7]+mat[6]*rhs.mat[11]+mat[7]*rhs.mat[15];

    temp.mat[8]=mat[8]*rhs.mat[0]+mat[9]*rhs.mat[4]+mat[10]*rhs.mat[8]+mat[11]*rhs.mat[12];
    temp.mat[9]=mat[8]*rhs.mat[1]+mat[9]*rhs.mat[5]+mat[10]*rhs.mat[9]+mat[11]*rhs.mat[13];
    temp.mat[10]=mat[8]*rhs.mat[2]+mat[9]*rhs.mat[6]+mat[10]*rhs.mat[10]+mat[11]*rhs.mat[14];
    temp.mat[11]=mat[8]*rhs.mat[3]+mat[9]*rhs.mat[7]+mat[10]*rhs.mat[11]+mat[11]*rhs.mat[15];

    temp.mat[12]=mat[12]*rhs.mat[0]+mat[13]*rhs.mat[4]+mat[14]*rhs.mat[8]+mat[15]*rhs.mat[12];
    temp.mat[13]=mat[12]*rhs.mat[1]+mat[13]*rhs.mat[5]+mat[14]*rhs.mat[9]+mat[15]*rhs.mat[13];
    temp.mat[14]=mat[12]*rhs.mat[2]+mat[13]*rhs.mat[6]+mat[14]*rhs.mat[10]+mat[15]*rhs.mat[14];
    temp.mat[15]=mat[12]*rhs.mat[3]+mat[13]*rhs.mat[7]+mat[14]*rhs.mat[11]+mat[15]*rhs.mat[15];

    return temp;
}

Vec4 Mat4::operator*(const Vec4 &rhs)
{
    Vec4 temp;
    temp.x=mat[0]*rhs.x+mat[1]*rhs.y+mat[2]*rhs.z+mat[3]*rhs.w;
    temp.y=mat[4]*rhs.x+mat[5]*rhs.y+mat[6]*rhs.z+mat[7]*rhs.w;
    temp.z=mat[8]*rhs.x+mat[9]*rhs.y+mat[10]*rhs.z+mat[11]*rhs.w;
    temp.w=mat[12]*rhs.x+mat[13]*rhs.y+mat[14]*rhs.z+mat[15]*rhs.w;
    return temp;
}
