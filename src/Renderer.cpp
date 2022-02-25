#include <cstdio>
#include <cstring>
#include <cassert>

#include <imgui.h>

#include <maths.hpp>

#include <Renderer.hpp>
#include <Light.hpp>

void rdrVertex::SetColor(float a1, float b1, float c1, float d1)
{
    r = a1;
    g = b1;
    b = c1;
    a = d1;
}

void rdrVertex::SetPosition(float a1, float b1, float c1)
{
    x = a1;
    y = b1;
    z = c1;
}

/*
Renderer::Renderer(float* p_colorBuffer32Bits, float* p_depthBuffer, const uint p_width, const uint p_height):
fb(p_width, p_height),viewport(0,0,p_width, p_height)
{
    //fb.colorBuffer = reinterpret_cast<Vec4*>(p_colorBuffer32Bits);
    //fb.depthBuffer = p_depthBuffer;

}
*/
Renderer::Renderer(Framebuffer *f, const uint p_width, const uint p_height) : viewport(0, 0, p_width, p_height)
{
    fb = f;
    Zbuffer = fb->GetDepthBuffer();
    rotX = M_PI;
    rotY = 0;
    rotZ = 0;
    transX = 0;
    transY = 0;
    transZ = 3;
    scaleX = 0.8;
    scaleY = 0.8;
    scaleZ = 0.8;

    posX = 0.f;
    posY = 0.f;
    posZ = -2.f;
}

Renderer::~Renderer()
{
}


void Renderer::SetProjection(float *p_projectionMatrix)
{

    for (int i = 0; i < 16; i++)
    {
        projMat.mat[i] = p_projectionMatrix[i];
    }
}

void Renderer::SetView(float *p_viewMatrix)
{
    // TODO
}

void Renderer::SetModel(float *p_modelMatrix)
{
    Mat4 transform = transform.CreateTransformMatrix({rotX, rotY, rotZ}, {transX, transY, transZ}, {scaleX, scaleY, scaleZ});
    for (int i = 0; i < 16; i++)
    {
        p_modelMatrix[i] = transform.mat[i];
    }

    //comm
}

void Renderer::SetViewport(const int p_x, const int p_y, const uint p_width, const uint p_height)
{
    // TODO
}

void Renderer::SetTexture(float *p_colors32Bits, const uint p_width, const uint p_height)
{
    // TODO
}

float edgeVertices(const Vec3 &ver1, const Vec3 &ver2, const Vec3 &ver3)
{
    float temp;
    temp = (ver3.x - ver1.x) * (ver2.y - ver1.y) - (ver3.y - ver1.y) * (ver2.x - ver1.x);
    return temp;
}

float GetMin(float a, float b, float c)
{
    if (a < b)
    {
        if (a < c)
        {
            return a;
        }
        else
        {
            return c;
        }
    }
    else
    {
        if (b < c)
        {
            return b;
        }
        else
        {
            return c;
        }
    }
}

float GetMax(float a, float b, float c)
{
    if (a > b)
    {
        if (a > c)
        {
            return a;
        }
        else
        {
            return c;
        }
    }
    else
    {
        if (b > c)
        {
            return b;
        }
        else
        {
            return c;
        }
    }
}

void Renderer::DrawPixel(const uint p_width, const uint p_height, const uint p_x, const uint p_y, const float p_z, const Vec4 p_color)
{
    float *colorBuffer = fb->GetColorBuffer();
    if (p_x <= p_width - 1 && p_y <= p_height - 1 && p_x >= 0 && p_y >= 0)
    {
        if (Zbuffer[p_x + p_y * p_width] < p_z)
        {
            Zbuffer[p_x + p_y * p_width] = p_z;
            colorBuffer[(p_x + p_y * p_width) * 4] = p_color.x;
            colorBuffer[(p_x + p_y * p_width) * 4 + 1] = p_color.y;
            colorBuffer[(p_x + p_y * p_width) * 4 + 2] = p_color.z;
            colorBuffer[(p_x + p_y * p_width) * 4 + 3] = p_color.w;
        }
    }
}



//
void Renderer::BarycenterGen(const Vec3 &ver1, const Vec3 &ver2, const Vec3 &ver3, const Vec3 &p, const Viewport vp, const Vec3 &Normal)
{
    float area = edgeVertices(ver1, ver2, ver3);
    float w0 = edgeVertices(ver2, ver3, p);
    float w1 = edgeVertices(ver3, ver1, p);
    float w2 = edgeVertices(ver1, ver2, p);

    Light light;
    light.positionLight.x = posX;
    light.positionLight.y = posY;
    light.positionLight.z = posZ;
    Vec4 colour;

    float ratio = light.GetLightRatio({0.f, 0.f, 0.f}, {Normal}, p);

    if (w0 >= 0 && w1 >= 0 && w2 >= 0)
    {
        w0 /= area;
        w1 /= area;
        w2 /= area;
        colour = {0, 0, 1, 1};
        DrawPixel(vp.width, vp.height, p.x, p.y, p.z, colour * ratio);
    }
}

void Renderer::DrawLine(const Vec3 &p0, const Vec3 &p1, const Vec4 &color)
{
    float x1 = p1.x;
    float y1 = p1.y;
    float x0 = p0.x;
    float y0 = p0.y;

    int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int dy = abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
    int err = dx - dy, e2, x2;
    int ed = dx + dy == 0 ? 1 : sqrt((float)dx * dx + (float)dy * dy);

    for (;;)
    { /* pixel loop */
        if (y0 > 0 && y0 < viewport.width * viewport.height && x0 > 0 && viewport.width * y0 < viewport.width * viewport.height && viewport.height * y0 < viewport.width * viewport.height)
        {
            DrawPixel(800, 600, x0, y0, p0.z, {color.x, color.y, color.z, color.w});
        }
        e2 = err;
        x2 = x0;
        if (2 * e2 >= -dx)
        {
            if (roundf(x0) == roundf(x1))
                break;
            if (e2 + dy < ed)
                if (y0 > 0 && y0 < viewport.width * viewport.height && x0 > 0 && viewport.width * y0 < viewport.width * viewport.height && viewport.height * y0 < viewport.width * viewport.height)
                {
                    DrawPixel(800, 600, x0, y0 + sy, p0.z, {color.x, color.y, color.z, color.w});
                }
            err -= dy;
            x0 += sx;
        }
        if (2 * e2 <= dy)
        {
            if (roundf(y0) == roundf(y1))
                break;
            if (dx - e2 < ed)
                if (y0 > 0 && y0 < viewport.width * viewport.height && x0 > 0 && viewport.width * y0 < viewport.width * viewport.height && viewport.height * y0 < viewport.width * viewport.height)
                {
                    DrawPixel(800, 600, x2 + sx, y0, p0.z, {color.x, color.y, color.z, color.w});
                }
            err += dx;
            y0 += sy;
        }
    }
}

Vec3 ndcToScreenCoords(Vec3 ndc, const Viewport &viewport)
{
    Vec3 screenCoords = {
        (0.5f + (ndc.x * 0.5f)) * viewport.width,
        (0.5f + (ndc.y * 0.5f)) * viewport.height,
        0.f};
    return screenCoords;
}

void Renderer::DrawQuad(rdrVertex *vertices)
{
    rdrVertex vert1[3];

    vert1[0] = vertices[2]; //2
    vert1[1] = vertices[0]; //0
    vert1[2] = vertices[1]; //1
    DrawTriangle(vert1);

    vert1[0] = vertices[0]; //2;
    vert1[1] = vertices[2]; //0;
    vert1[2] = vertices[3]; //3;
    DrawTriangle(vert1);
}

void Renderer::DrawTriangle(rdrVertex *vertices)
{
    // Store triangle vertices positions
    Vec3 localCoords[3] = {
        {vertices[0].x, vertices[0].y, vertices[0].z},
        {vertices[1].x, vertices[1].y, vertices[1].z},
        {vertices[2].x, vertices[2].y, vertices[2].z},
    };
    
    // Local space (v3) -> World space (v4)

    Vec4 worldCoords[3] = {
        {Vec4{localCoords[0], 1.f}},
        {Vec4{localCoords[1], 1.f}},
        {Vec4{localCoords[2], 1.f}},
    };
    Mat4 transform = transform.identity();

    SetModel(transform.mat);

    worldCoords[0] = transform * worldCoords[0];
    worldCoords[1] = transform * worldCoords[1];
    worldCoords[2] = transform * worldCoords[2];

    // World space (v4) -> Clip space (v4)
    Vec4 clipCoords[3] = {
        projMat * worldCoords[0],
        projMat * worldCoords[1],
        projMat * worldCoords[2],
    };


    // Clip space (v4) to NDC (v3)
    
    Vec3 ndcCoords[3] = {
        {clipCoords[0].x / clipCoords[0].w, clipCoords[0].y / clipCoords[0].w, clipCoords[0].z / clipCoords[0].w},
        {clipCoords[1].x / clipCoords[1].w, clipCoords[1].y / clipCoords[1].w, clipCoords[1].z / clipCoords[1].w},
        {clipCoords[2].x / clipCoords[2].w, clipCoords[2].y / clipCoords[2].w, clipCoords[2].z / clipCoords[2].w},
    };

    
    // NDC (v3) to screen coords (v2)
    
    Vec3 screenCoords[3] = {
        {ndcToScreenCoords(ndcCoords[0], viewport)},
        {ndcToScreenCoords(ndcCoords[1], viewport)},
        {ndcToScreenCoords(ndcCoords[2], viewport)},
    };
    //Get Bounding box
    int iMin = (int)GetMin(screenCoords[0].x, screenCoords[1].x, screenCoords[2].x);
    int iMax = (int)GetMax(screenCoords[0].x, screenCoords[1].x, screenCoords[2].x);
    int jMin = (int)GetMin(screenCoords[0].y, screenCoords[1].y, screenCoords[2].y);
    int jMax = (int)GetMax(screenCoords[0].y, screenCoords[1].y, screenCoords[2].y);

    //Get Norm
    Vec3 normal = CrossProduct(ndcCoords[1] - ndcCoords[0], ndcCoords[2] - ndcCoords[0]);
    // Draw triangle wireframe

    if (wireframe)
    {
        DrawLine(screenCoords[0], screenCoords[1], lineColor);
        DrawLine(screenCoords[1], screenCoords[2], lineColor);
        DrawLine(screenCoords[0], screenCoords[2], lineColor);
    }
    else
    {
        for (int i = iMin; i < iMax; i++)
        {
            for (int j = jMin; j < jMax; j++)
            {
                BarycenterGen(screenCoords[0], screenCoords[1], screenCoords[2], {i, j, (ndcCoords[0].z + ndcCoords[1].z + ndcCoords[2].z) / 3}, viewport, normal);
            }
        }
    }
}

void Renderer::DrawTriangles(rdrVertex *p_vertices, const uint p_count)
{
    // calculate mvp from matrices
    // Transform vertex list to triangles into colorBuffer
    for (uint i = 0; i < p_count; i += 3)
    {
        DrawTriangle(&p_vertices[i]);
    }
}

void Renderer::DrawQuads(rdrVertex *p_vertices, const uint p_count)
{
    // calculate mvp from matrices
    // Transform vertex list to triangles into colorBuffer
    for (uint i = 0; i < p_count; i += 4)
    {
        DrawQuad(&p_vertices[i]);
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
    ImGui::Checkbox("Wireframe", &wireframe);
    ImGui::SliderFloat("rotX", &rotX, 0, M_PI * 2);
    ImGui::SliderFloat("rotY", &rotY, 0, M_PI * 2);
    ImGui::SliderFloat("rotZ", &rotZ, 0, M_PI * 2);

    ImGui::SliderFloat("transX", &transX, 0, M_PI * 2);
    ImGui::SliderFloat("transY", &transY, 0, M_PI * 2);
    ImGui::SliderFloat("transZ", &transZ, 0, M_PI * 2);

    ImGui::SliderFloat("scaleX", &scaleX, 0, M_PI * 2);
    ImGui::SliderFloat("scaleY", &scaleY, 0, M_PI * 2);
    ImGui::SliderFloat("scaleZ", &scaleZ, 0, M_PI * 2);

    ImGui::SliderFloat("posX", &posX, -100, 100);
    ImGui::SliderFloat("posY", &posY, -100, 100);
    ImGui::SliderFloat("posZ", &posZ, -100, 100);
}
