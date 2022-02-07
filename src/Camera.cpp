
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
    //TODO
    return Mat4::identity();
}

void Camera::ShowImGuiControls()
{
    //TODO
}