#pragma once
#include <vector>
#include <Renderer.hpp>


class Scene
{
private:
    double time = 0.0;
    std::vector<rdrVertex> vertices;
    std::vector<rdrVertex> vertices1;

    Vec3 *cubeVertice ;
    float rotX,rotY,rotZ,transX,transY,transZ,scale,scaleX,scaleY,scaleZ;

    bool isExo1=false;
    
public:
    Scene();
    ~Scene();
    void Update(float p_deltaTime, Renderer& p_renderer);
    void DrawSphere(const int lon, const int lat, const float& radius, const Vec3& rotation, Vec3 translation,const Vec3& scale,Vec3 position, Renderer& renderer);
    void ShowImGuiControls();

private:
    

};


