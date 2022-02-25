#pragma once

#include <types.hpp>
#include <Framebuffer.hpp>

// Vertex format (only one supported for now)
class rdrVertex
{   
    public:
    float x, y, z;    // Pos
    float nx, ny, nz; // Normal
    float r, g, b, a; // Color
    float u, v;       // Texture coordinates
    void SetPosition(float a1, float b1, float c1);
    void SetColor(float a1, float b1, float c1, float d1);
};


struct Viewport
{

    Viewport(const int p_x, const int p_y, uint p_width, uint p_height):
    x(p_x),y(p_y),width(p_width),height(p_height){}

    const int x;
    const int y;
    uint width; 
    uint height;
};


class Renderer
{
private:
    Framebuffer* fb;
    float *Zbuffer;
    Viewport viewport;
    float lineColor[3] = {0,255,0};
    Mat4 modelMat;
    Mat4 projMat;
    Mat4 viewMat;

    bool wireframe=false;
    bool uniCol=true;
    bool isLight=true;

public:
    float posX,posY,posZ;
// Color and depth buffer have to be valid until the shutdown of the renderer
// Color buffer is RGBA, each component is a 32 bits float
// Depth buffer is a buffer of 32bits floats
    //Renderer(float* p_colorBuffer32Bits, float* p_depthBuffer, uint p_width, uint p_height);
    Renderer(Framebuffer* f,const uint p_width, const uint p_height);
    ~Renderer();

    //TODO
    void SetProjection(float* p_projectionMatrix);
    void SetView(float* p_viewMatrix);
    void SetModel(float* p_modelMatrix);
    bool OnScreen(const Vec3 coord);
    void SetViewport(const int p_x, const int p_y, const uint p_width, const uint p_height);
    void SetTexture(float* p_colors32Bits, const uint p_width, const uint p_height);
    void DrawLine(const Vec3& p_0, const Vec3& p_1, const Vec4& p_color);
    void DrawTriangles(rdrVertex* p_vertices, const uint p_count);
    void DrawQuads(rdrVertex* p_vertices, const uint p_count );
    void DrawPixel(uint p_width, uint p_height, uint p_x, uint p_y,const float p_z, Vec4 p_color);
    void BarycenterGen(const Vec3 &ver1, const Vec3 &ver2, const Vec3 &ver3, float iMin, float iMax, float jMin, float jMax, float z, const Viewport vp, const Vec3 &Normal);
    
    void ShowImGuiControls();

private:
    void DrawTriangle(rdrVertex *vertices);
    void DrawQuad(rdrVertex* p_vertices);
    
};

