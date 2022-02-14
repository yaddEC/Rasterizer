#include <imgui.h>
#include <maths.hpp>
#include <Scene.hpp>

Vec3 *CubeGen(Vec3 startPos, float size, Vec3 verts[])
{
    float l = size / 2;

    for (int i = 0; i < 8; i++)
    {
        verts[i] = {
            (i & 4) != 0 ? l : -l,
            (i & 2) != 0 ? l + startPos.y : -l + startPos.y,
            (i & 1) != 0 ? l + startPos.z : -l + startPos.z};
    }
    return verts;
}

Scene::Scene()
{
    // HERE: Load the scene
    // Setup some vertices to test
    Vec3 cube[8];

    cubeVertice = CubeGen({-0.5, 0, 2}, 1, cube);
    vertices = {
        //       pos                  normal                  color              uv
        {-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f},
        {0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f},
        {0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f},

    };
    vertices1 = {
        //       pos                  normal                  color              uv
        {cubeVertice[1].x, cubeVertice[1].y, cubeVertice[1].z, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f},
        {cubeVertice[0].x, cubeVertice[0].y, cubeVertice[0].z, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f},
        {cubeVertice[2].x, cubeVertice[2].y, cubeVertice[2].z, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f},
        {cubeVertice[3].x, cubeVertice[3].y, cubeVertice[3].z, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f},

    };
    vertices2 = {
        //       pos                  normal                  color              uv
        {cubeVertice[3].x, cubeVertice[3].y, cubeVertice[3].z, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f},
        {cubeVertice[2].x, cubeVertice[2].y, cubeVertice[2].z, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f},
        {cubeVertice[6].x, cubeVertice[6].y, cubeVertice[6].z, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f},
        {cubeVertice[7].x, cubeVertice[7].y, cubeVertice[7].z, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f},

    };
    vertices3 = {
        //       pos                  normal                  color              uv
        {cubeVertice[5].x, cubeVertice[5].y, cubeVertice[5].z, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f},
        {cubeVertice[4].x, cubeVertice[4].y, cubeVertice[4].z, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f},
        {cubeVertice[0].x, cubeVertice[0].y, cubeVertice[0].z, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f},
        {cubeVertice[1].x, cubeVertice[1].y, cubeVertice[1].z, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f},

    };
    vertices4 = {
        //       pos                  normal                  color              uv
        {cubeVertice[4].x, cubeVertice[4].y, cubeVertice[4].z, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f},
        {cubeVertice[5].x, cubeVertice[5].y, cubeVertice[5].z, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f},
        {cubeVertice[7].x, cubeVertice[7].y, cubeVertice[7].z, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f},
        {cubeVertice[6].x, cubeVertice[6].y, cubeVertice[6].z, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f},
    };
    vertices5 = {
        //       pos                  normal                  color              uv
        {cubeVertice[6].x, cubeVertice[6].y, cubeVertice[6].z, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f},
        {cubeVertice[2].x, cubeVertice[2].y, cubeVertice[2].z, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f},
        {cubeVertice[0].x, cubeVertice[0].y, cubeVertice[0].z, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f},
        {cubeVertice[4].x, cubeVertice[4].y, cubeVertice[4].z, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f},

    };
    vertices6 = {
        //       pos                  normal                  color              uv
        {cubeVertice[3].x, cubeVertice[3].y, cubeVertice[3].z, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f},
        {cubeVertice[7].x, cubeVertice[7].y, cubeVertice[7].z, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f},
        {cubeVertice[5].x, cubeVertice[5].y, cubeVertice[5].z, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f},
        {cubeVertice[1].x, cubeVertice[1].y, cubeVertice[1].z, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f},

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

    renderer.DrawQuads(vertices1.data(), (int)vertices.size(), {rot, rot1, rot2}, {scalex, 250, 200}, {200, 200, 200});
    renderer.DrawQuads(vertices2.data(), (int)vertices.size(), {rot, rot1, rot2}, {scalex, 250, 200}, {200, 200, 200});
    renderer.DrawQuads(vertices3.data(), (int)vertices.size(), {rot, rot1, rot2}, {scalex, 250, 200}, {200, 200, 200});
    renderer.DrawQuads(vertices4.data(), (int)vertices.size(), {rot, rot1, rot2}, {scalex, 250, 200}, {200, 200, 200});
    renderer.DrawQuads(vertices5.data(), (int)vertices.size(), {rot, rot1, rot2}, {scalex, 250, 200}, {200, 200, 200});
    renderer.DrawQuads(vertices6.data(), (int)vertices.size(), {rot, rot1, rot2}, {scalex, 250, 200}, {200, 200, 200});

    if (isExo1)
        renderer.DrawTriangles(vertices.data(), (int)vertices.size(), {M_PI, 0, 0}, {450, 250, 0}, {200, 200, 0});

    time += deltaTime;
}

void Scene::ShowImGuiControls()
{

    ImGui::SliderFloat("rot1", &rot1, 0.f, 2 * M_PI);
    ImGui::SliderFloat("rot2", &rot2, 0.f, 2 * M_PI);
    ImGui::SliderFloat("rot", &rot, 0.f, 2 * M_PI);
    ImGui::SliderFloat("scalex", &scalex, 100.f, 600.f);

    ImGui::Checkbox("Exo 1", &isExo1);
}
