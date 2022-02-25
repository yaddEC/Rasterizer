#pragma once
#include <vector>
#include <Renderer.hpp>
#include <Light.hpp>

class Scene
{
private:
    double time = 0.0;
    std::vector<rdrVertex> vertices;
    std::vector<rdrVertex> vertices1;
    std::vector<Light> light;
    Mat4 transform;
    Vec3 *cubeVertice;

    float rotX, rotY, rotZ, transX, transY, transZ, scale, scaleX, scaleY, scaleZ;

    bool isExo1 = false;

public:
    Scene();
    ~Scene();
    void Update(float p_deltaTime, Renderer &p_renderer);
    void DrawSphere(const int lon, const int lat, const float &radius, Vec3 translation, Renderer &renderer);
    void ShowImGuiControls();

private:
};
