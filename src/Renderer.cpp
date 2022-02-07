
#include <cstdio>
#include <cstring>
#include <cassert>

#include <imgui.h>

#include <maths.hpp>

#include <Renderer.hpp>



Renderer::Renderer(float* p_colorBuffer32Bits, float* p_depthBuffer, const uint p_width, const uint p_height):
fb(p_width, p_height),viewport(0,0,p_width, p_height)
{
    //fb.colorBuffer = reinterpret_cast<Vec4*>(p_colorBuffer32Bits);
    //fb.depthBuffer = p_depthBuffer;

}

Renderer::~Renderer()
{

}

void Renderer::SetProjection(float* p_projectionMatrix)
{
    // TODO
}

void Renderer::SetView(float* p_viewMatrix)
{
    // TODO
}

void Renderer::SetModel(float* p_modelMatrix)
{
    // TODO
}

void Renderer::SetViewport(const int p_x, const int p_y, const uint p_width, const uint p_height)
{
    // TODO
}

void Renderer::SetTexture(float* p_colors32Bits, const uint p_width, const uint p_height)
{
    // TODO
}

void DrawPixel(Vec4* p_colorBuffer, uint p_width, uint p_height, uint p_x, uint p_y, Vec4 p_color)
{
    // TODO
}
void Renderer::DrawLine(const Vec3& p0, const Vec3& p1, const Vec4& color)
{
   //TODO
}

Vec3 ndcToScreenCoords(Vec3 ndc, const Viewport& viewport)
{
    // TODO
    return ndc;
}

void Renderer::DrawTriangle(rdrVertex* vertices)
{
    // Store triangle vertices positions
    Vec3 localCoords[3] = {
        { vertices[0].x, vertices[0].y, vertices[0].z },
        { vertices[1].x, vertices[1].y, vertices[1].z },
        { vertices[2].x, vertices[2].y, vertices[2].z },
    };

    // Local space (v3) -> Clip space (v4)
    // TODO
    Vec4 clipCoords[3] = {
        { Vec4{ localCoords[0], 1.f } },
        { Vec4{ localCoords[1], 1.f } },
        { Vec4{ localCoords[2], 1.f } },
    };

    // Clip space (v4) to NDC (v3)
    // TODO
    Vec3 ndcCoords[3] = {
        { clipCoords[0].x,clipCoords[0].y,clipCoords[0].z },
        {  clipCoords[1].x,clipCoords[1].y,clipCoords[1].z },
        {  clipCoords[2].x,clipCoords[2].y,clipCoords[2].z},
    };

    // NDC (v3) to screen coords (v2)
    // TODO
    Vec3 screenCoords[3] = {
        { ndcToScreenCoords(ndcCoords[0], viewport) },
        { ndcToScreenCoords(ndcCoords[1], viewport) },
        { ndcToScreenCoords(ndcCoords[2], viewport) },
    };

    // Draw triangle wireframe
    DrawLine(screenCoords[0], screenCoords[1], lineColor);
    DrawLine(screenCoords[1], screenCoords[2], lineColor);
    DrawLine(screenCoords[2], screenCoords[0], lineColor);
}

void Renderer::DrawTriangles(rdrVertex* p_vertices, const uint p_count)
{
    // calculate mvp from matrices
    // Transform vertex list to triangles into colorBuffer
    for (int i = 0; i < p_count; i += 3)
    {
        DrawTriangle(&p_vertices[i]);
    }
}
/*
void rdrSetImGuiContext(rdrImpl* renderer, struct ImGuiContext* context)
{
    ImGui::SetCurrentContext(context);
}*/

void Renderer::ShowImGuiControls()
{
    ImGui::ColorEdit4("lineColor", &lineColor.x);
}
