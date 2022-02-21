
#include <imgui.h>

#include <maths.hpp>

#include <Camera.hpp>

Camera::Camera(const uint width, const uint height)
{
    //TODO
    // width and height are useful to compute projection matrix with the right aspect ratio
}

void Camera::Update(const float p_deltaTime, const CameraInputs& inputs)
{
    //TODO
}

Mat4 Camera::GetViewMatrix()
{
    //TODO
    return Mat4::identity();
}

Mat4 Camera::GetProjection()
{
        float f =100;// far clipping plane
    float n = 2; // near clipping plane
    float fov = 60;
    float s = 1/tanf((fov/2)*(M_PI/180));
    float c = f/(f-n);
    float array[16]
    ={
         
        s, 0.f, 0.f, 0.f,
        0.f, s, 0.f, 0.f,
        0.f, 0.f, -c, -1.f,
        0.f, 0.f, -(c*n), 0.f,
        
    };
    return array;
}

void Camera::ShowImGuiControls()
{
    //TODO
}