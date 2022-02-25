
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
    if(inputs.deltaX>0)
    {
        to.x+=-inputs.deltaX*p_deltaTime;
        to.y+=inputs.deltaY*p_deltaTime;
    }

    else if(inputs.deltaX<0)
    {
        to.x+=-inputs.deltaX*p_deltaTime;
        to.y+=inputs.deltaY*p_deltaTime;
    }
   

    if (inputs.moveForward)
        {
            from.x = from.x + 1.f * sin(to.x);
            from.z = from.z + 1.f * cos(to.x);
            to.x = from.x + sin(to.x) * cos(to.y);
            to.z = from.z + cos(to.x) * cos(to.y);
        }
        else if (inputs.moveBackward)
        {
            from.x = from.x - 1.f * sin(to.x) / 2.f;
            from.z = from.z - 1.f * cos(to.x) / 2.f;
            to.x = from.x + sin(to.x) * cos(to.y);
            to.z = from.z + cos(to.x) * cos(to.y);
        }
}

Mat4 Camera::GetViewMatrix()
{
    Vec3 tmp = {0, 1, 0};
    tmp.Normalize();
    Vec3 forward = from - to; 
    forward.Normalize();
    Vec3 right = CrossProduct(tmp, forward); 
    Vec3 up = CrossProduct(forward, right); 
    float array[16] = 
    {
        right.x,right.y,right.z,0,
        up.x,up.y,up.z,0,
        forward.x,forward.y,forward.z,0,
        from.x,from.y,from.z,1
    };
 
    return array; 
}

Mat4 Camera::GetProjection()
{
    float f =2;// far clipping plane
    float n = 1; // near clipping plane
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