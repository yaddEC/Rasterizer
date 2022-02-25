#pragma once

#include <types.hpp>
#include <Framebuffer.hpp>
class Light
{
public:
    Vec3 positionLight;
    float ambientComponent;
    float diffuseComponent;
    float specularComponent;

    Light(/* args */);
    float GetLightRatio(const Vec3 ViewVec,const Vec3 NormalVec,Vec3 test);
    ~Light();
};