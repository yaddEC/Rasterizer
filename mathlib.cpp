#include "mathlib.hpp"
#include "math.h"

Vec3::Vec3()
{
    x = 0;
    y = 0;
    z = 0;
}

Vec3::Vec3(float a, float b, float c)
{
    x = a;
    y = b;
    z = c;
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
    x = 0;
    y = 0;
    z = 0;
    w = 0;
}

Vec4::Vec4(float a, float b, float c, float d)
{
    x = a;
    y = b;
    z = c;
    w = d;
}

Vec4::Vec4(const Vec3 &vec3, float _w)
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

void Vec4::Print()
{
    printf("\n|%f|%f|%f|%f|\n\n", x, y, z, w);
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
    for (int i = 0; i < 16; i++)
    {
        mat[i] = 0;
    }
}

void Mat4::Print()
{
    printf("\n");
    printf("-------------------------\n");
    for (int i = 0; i < 16; i++)
    {
        if (i % 4 == 0)
            printf("|");

        printf(" %d ", (int)mat[i]);
        printf("|");
        if (i % 4 == 3)
            printf("\n-------------------------\n");
    }
    printf("\n");
}

Mat4::Mat4(const float (&arr)[16])
{
    for (int i = 0; i < 16; i++)
    {
        mat[i] = arr[i];
    }
}



Mat4 Mat4::operator*(const Mat4 &rhs)
{
    Mat4 temp;

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            for (int k = 0; k < 4; k++)
            {
                temp.mat[i*4+j] += mat[i*4+k] * rhs.mat[k*4+j];
            }
        }
    }

    return temp;
}

Vec4 Mat4::operator*(const Vec4 &rhs)
{
    Vec4 temp;
    temp.x = mat[0] * rhs.x + mat[1] * rhs.y + mat[2] * rhs.z + mat[3] * rhs.w;
    temp.y = mat[4] * rhs.x + mat[5] * rhs.y + mat[6] * rhs.z + mat[7] * rhs.w;
    temp.z = mat[8] * rhs.x + mat[9] * rhs.y + mat[10] * rhs.z + mat[11] * rhs.w;
    temp.w = mat[12] * rhs.x + mat[13] * rhs.y + mat[14] * rhs.z + mat[15] * rhs.w;
    return temp;
}

Mat4 Mat4::CreateTranslationMatrix(const Vec3 &translation)
{
    float array[16] =
        {
            1, 0, 0, translation.x,
            0, 1, 0, translation.y,
            0, 0, 1, translation.z,
            0, 0, 0, 1};
    Mat4 temp = array;
    return temp;
}
Mat4 Mat4::CreateScaleMatrix(const Vec3 &scale)
{
    float array[16] =
        {
            scale.x, 0, 0, 0,
            0, scale.y, 0, 0,
            0, 0, scale.z, 0,
            0, 0, 0, 1};
    Mat4 temp = array;
    return temp;
}
Mat4 Mat4::CreateXRotationMatrix(float angle)
{
    float array[16] =
        {
            1, 0, 0, 0,
            0, cos(angle), sin(angle), 0,
            0, -sin(angle), cos(angle), 0,
            0, 0, 0, 1};
    Mat4 temp = array;
    return temp;
}
Mat4 Mat4::CreateYRotationMatrix(float angle)
{
    float array[16] =
        {
            cos(angle), 0, -sin(angle), 0,
            0, 1, 0, 0,
            sin(angle), 0, cos(angle), 0,
            0, 0, 0, 1};
    Mat4 temp = array;
    return temp;
}
Mat4 Mat4::CreateZRotationMatrix(float angle)
{
    float array[16] =
        {
            cos(angle), -sin(angle), 0, 0,
            sin(angle), cos(angle), 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1};
    Mat4 temp = array;
    return temp;
}
Mat4 Mat4::CreateTransformMatrix(const Vec3& rotation, const Vec3& position, const Vec3& scale)
{
    return CreateXRotationMatrix(rotation.x)*CreateYRotationMatrix(rotation.y)*CreateZRotationMatrix(rotation.z)*CreateScaleMatrix(scale)*CreateTranslationMatrix(position);

}

void Mat4::TransposeMatrix(const int M,const int N) {
   
   Mat4 temp = mat;
    for (int i = 0; i < M; ++i )
    {
       for (int j = 0; j < N; ++j )
       {
          int index = i*N+j;
          int index2 = j*M+i;
          mat[index2] = temp.mat[index];
       }
    }
}

Mat4::~Mat4()
{
}

