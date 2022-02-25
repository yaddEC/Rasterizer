#pragma once
#include <mathlib.hpp>
#include <types.hpp>

struct CameraInputs
{
    float deltaX;
    float deltaY;
    bool moveForward;
    bool moveBackward;
    // ... and more if needed
};

class Camera
{
private:
public:
    Vec3 from = {0,0,2};
    Vec3 to = {0,0,0};
    Vec3 move = {0,0,0};
    Camera(const uint p_width, const uint p_height);

    void Update(const float p_deltaTime, const CameraInputs& p_inputs);
    Mat4 GetViewMatrix();
    Mat4 GetProjection();

    void ShowImGuiControls();
};