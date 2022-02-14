#include <imgui.h>
#include <maths.hpp>
#include <Scene.hpp>

Scene::Scene()
{
    // HERE: Load the scene
    // Setup some vertices to test
    vertices = {
        //       pos                  normal                  color              uv
        {-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f},
        {0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f},
        {0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f},


    };
    vertices2 = {
        //       pos                  normal                  color              uv
        {-1.5f, -1.f, 2.f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f},
        {0.5f, -1.f, 2.f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f},
        {0.5f, 1.f, 2.f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f},
        {-1.5f, 1.f, 2.f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f},

    };
}

Scene::~Scene()
{
    // HERE: Unload the scene
}

void Scene::Update(float deltaTime, Renderer &renderer)
{
    // HERE: Update (if needed) and display the scene

    // Hard coded matrix
    // TODO: Remove this and use proper functions !
    Mat4 matrix = {
        scale,
        0.f,
        0.f,
        0.f,
        0.f,
        scale,
        0.f,
        0.f,
        0.f,
        0.f,
        scale,
        0.f,
        (float)cos(time) * 0.5f,
        (float)sin(time) * 0.1f,
        0.f,
        1.f,
    };

    renderer.SetModel(matrix.mat);

    // Draw
    renderer.DrawQuads(vertices2.data(), (int)vertices.size(),{M_PI, 0, 0}, {450, 250, 0}, {200, 200, 0});
    if (isExo1)
        renderer.DrawTriangles(vertices.data(), (int)vertices.size(),{M_PI, 0, 0}, {450, 250, 0}, {200, 200, 0});

    time += deltaTime;
}

void Scene::ShowImGuiControls()
{
    ImGui::SliderFloat("scale", &scale, 0.f, 10.f);
    ImGui::Checkbox("Exo 1", &isExo1);
}
