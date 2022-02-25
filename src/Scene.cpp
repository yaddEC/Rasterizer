#include <imgui.h>
#include <maths.hpp>
#include <Scene.hpp>

Vec3 *CubeGen(Vec3 startPos, float size, Vec3 points[])
{
    float l = size / 2;

    for (int i = 0; i < 8; i++)
    {
        points[i] = {
            (i & 4) != 0 ? l : -l,
            (i & 2) != 0 ? l + startPos.y : -l + startPos.y,
            (i & 1) != 0 ? l + startPos.z : -l + startPos.z};
    }
    return points;
}

inline Vec3 getSphericalCoords(const float r, const float theta, const float phi)
{
    return {r * sinf(theta) * cosf(phi),
            r * cosf(theta),
            r * sinf(theta) * sinf(phi)};
}

void Scene::DrawSphere(const int lon, const int lat, const float &radius, Vec3 translation, Renderer &renderer)
{
    rdrVertex vertices[4];

    for (int j = 0; j < lat; ++j)
    {
        float theta0 = ((j + 0) / (float)lat) * M_PI;
        float theta1 = ((j + 1) / (float)lat) * M_PI;

        for (int i = 0; i < lon; ++i)
        {
            float phi0 = ((i + 0) / (float)lon) * 2.f * M_PI;
            float phi1 = ((i + 1) / (float)lon) * 2.f * M_PI;

            Vec4 c0 = getSphericalCoords(radius, theta0, phi0);
            Vec4 c1 = getSphericalCoords(radius, theta0, phi1);
            Vec4 c2 = getSphericalCoords(radius, theta1, phi1);
            Vec4 c3 = getSphericalCoords(radius, theta1, phi0);

            Mat4 transform = transform.CreateTranslationMatrix(translation);
            c0 = transform * c0;
            c1 = transform * c1;
            c2 = transform * c2;
            c3 = transform * c3;

            vertices[0].SetPosition(c0.x, c0.y, c0.z);
            vertices[1].SetPosition(c1.x, c1.y, c1.z);
            vertices[2].SetPosition(c2.x, c2.y, c2.z);
            vertices[3].SetPosition(c3.x, c3.y, c3.z);

            renderer.DrawQuads(vertices, 1);
        }
    }
}

Scene::Scene()
{
    // HERE: Load the scene
    // Setup some vertices to test
    Vec3 cube[8];
    rotX = M_PI;
    rotY = 0;
    rotZ = 0;
    transX = 0;
    transY = 0;
    transZ = 3;
    scaleX = 0.8;
    scaleY = 0.8;
    scaleZ = 0.8;
    scale = 1.f;
    cubeVertice = CubeGen({-0.5, 0, -1}, -1.5, cube);
    vertices = {
        //       pos                  normal                  color              uv
        {-0.5f, -0.5f, 5.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f},
        {0.5f, -0.5f, 5.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f},
        {0.0f, 0.5f, 5.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f},

    };
    vertices1 = {
        //       pos                  normal                  color              uv
        {cubeVertice[1].x, cubeVertice[1].y, cubeVertice[1].z, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f},
        {cubeVertice[0].x, cubeVertice[0].y, cubeVertice[0].z, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f},
        {cubeVertice[2].x, cubeVertice[2].y, cubeVertice[2].z, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f},
        {cubeVertice[3].x, cubeVertice[3].y, cubeVertice[3].z, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f},
        {cubeVertice[3].x, cubeVertice[3].y, cubeVertice[3].z, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f},
        {cubeVertice[2].x, cubeVertice[2].y, cubeVertice[2].z, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f},
        {cubeVertice[6].x, cubeVertice[6].y, cubeVertice[6].z, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f},
        {cubeVertice[7].x, cubeVertice[7].y, cubeVertice[7].z, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f},
        {cubeVertice[5].x, cubeVertice[5].y, cubeVertice[5].z, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f},
        {cubeVertice[4].x, cubeVertice[4].y, cubeVertice[4].z, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f},
        {cubeVertice[0].x, cubeVertice[0].y, cubeVertice[0].z, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f},
        {cubeVertice[1].x, cubeVertice[1].y, cubeVertice[1].z, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f},
        {cubeVertice[4].x, cubeVertice[4].y, cubeVertice[4].z, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f},
        {cubeVertice[5].x, cubeVertice[5].y, cubeVertice[5].z, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f},
        {cubeVertice[7].x, cubeVertice[7].y, cubeVertice[7].z, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f},
        {cubeVertice[6].x, cubeVertice[6].y, cubeVertice[6].z, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f},
        {cubeVertice[6].x, cubeVertice[6].y, cubeVertice[6].z, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f},
        {cubeVertice[2].x, cubeVertice[2].y, cubeVertice[2].z, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f},
        {cubeVertice[0].x, cubeVertice[0].y, cubeVertice[0].z, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f},
        {cubeVertice[4].x, cubeVertice[4].y, cubeVertice[4].z, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f},
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

    // Draw
    transform = transform.CreateTransformMatrix({rotX, rotY, rotZ}, {transX, transY, transZ}, {scaleX, scaleY, scaleZ});
    renderer.SetModel(transform.mat);
    DrawSphere(20, 20, 1, {0.5, 0, 1}, renderer);
    renderer.DrawQuads(vertices1.data(), (int)vertices1.size());
    if (isExo1)
        renderer.DrawTriangles(vertices.data(), (int)vertices.size());

    time += deltaTime;
}

//Donaudampfschifffahrtsgesellschaftskapitaenswitwe
void Scene::ShowImGuiControls()
{

    ImGui::SliderFloat("rotX", &rotX, 0, M_PI * 2);
    ImGui::SliderFloat("rotY", &rotY, 0, M_PI * 2);
    ImGui::SliderFloat("rotZ", &rotZ, 0, M_PI * 2);

    ImGui::SliderFloat("transX", &transX, 0, M_PI * 2);
    ImGui::SliderFloat("transY", &transY, 0, M_PI * 2);
    ImGui::SliderFloat("transZ", &transZ, 0, M_PI * 2);

    ImGui::SliderFloat("scaleX", &scaleX, 0, M_PI * 2);
    ImGui::SliderFloat("scaleY", &scaleY, 0, M_PI * 2);
    ImGui::SliderFloat("scaleZ", &scaleZ, 0, M_PI * 2);
    ImGui::Checkbox("Exo 1", &isExo1);
}
