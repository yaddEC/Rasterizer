#pragma once
#include <vector>
#include <Renderer.hpp>

class Scene
{
private:
    double time = 0.0;
    std::vector<rdrVertex> vertices;
    std::vector<rdrVertex> vertices1;
    std::vector<rdrVertex> vertices2;
    std::vector<rdrVertex> vertices3;
    std::vector<rdrVertex> vertices4;
    std::vector<rdrVertex> vertices5;
    std::vector<rdrVertex> vertices6;
    Vec3 *cubeVertice ;
    float rot1,rot2;
    float scalex=0.f;
float scale=1.f;
    float rot=0;
    bool isExo1=false;
    
public:
    Scene();
    ~Scene();
    void Update(float p_deltaTime, Renderer& p_renderer);
    void ShowImGuiControls();

private:
    

};


