#pragma once
#include <vector>
#include <Renderer.hpp>

class Scene
{
private:
    double time = 0.0;
    std::vector<rdrVertex> vertices;
    std::vector<rdrVertex> vertices2;
    float scale = 1.f;
    bool isExo1=false;
    
public:
    Scene();
    ~Scene();
    void Update(float p_deltaTime, Renderer& p_renderer);
    void ShowImGuiControls();

private:
    

};


