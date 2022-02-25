

#include <Light.hpp>

#include <maths.hpp>

#include <Renderer.hpp>
Light::Light()
{
    positionLight = {0.f, 0.f, 0.f};
    ambientComponent = 0.2f;
    diffuseComponent = 0.4f;
    specularComponent = 0.4f;
}

Light::~Light()
{
}

float Light::GetLightRatio(Vec3 ViewVec, Vec3 NormalVec, Vec3 pPos)
{

    Vec3 DirLight = (positionLight - pPos);
    DirLight.Normalize();
    Vec3 camDir = ViewVec - pPos;
    camDir.Normalize();
    camDir.x =fabs(camDir.x);
    camDir.y =fabs(camDir.y);
    camDir.z =fabs(camDir.z);
    
    NormalVec.Normalize();
    float diffuse = dot(NormalVec, DirLight);
 
    /* else
        diffuse = 0; */
    Vec3 temp = ((NormalVec * 2.f) * dot(NormalVec, DirLight)) - DirLight;
    temp.Normalize();

    float specular = dot(camDir, temp);
    if (specular > 1)
    {
        specular = 1;

        specular = pow(specular, 0.2f * 64.f);
    }

    specular *= specularComponent;
    diffuse *= diffuseComponent;

    return specular + diffuse +ambientComponent;
}