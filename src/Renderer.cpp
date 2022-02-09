#include <cstdio>
#include <cstring>
#include <cassert>

#include <imgui.h>

#include <maths.hpp>

#include <Renderer.hpp>


/*
Renderer::Renderer(float* p_colorBuffer32Bits, float* p_depthBuffer, const uint p_width, const uint p_height):
fb(p_width, p_height),viewport(0,0,p_width, p_height)
{
    //fb.colorBuffer = reinterpret_cast<Vec4*>(p_colorBuffer32Bits);
    //fb.depthBuffer = p_depthBuffer;

}
*/
Renderer::Renderer(Framebuffer* f,const uint p_width, const uint p_height):viewport(0,0,p_width, p_height)
{
    fb = f;
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

void Renderer::DrawPixel(uint p_width, uint p_height, uint p_x, uint p_y, color4 p_color)
{
    float* colorBuffer = fb->GetColorBuffer();
    
    colorBuffer[(p_x + p_y*p_width) *4] = p_color.r;
    colorBuffer[(p_x + p_y*p_width) *4 + 1] = p_color.g;
    colorBuffer[(p_x + p_y*p_width) *4 + 2] = p_color.b;
    colorBuffer[(p_x + p_y*p_width) *4 + 3] = p_color.a;
}
void Renderer::DrawLine(const Vec3& p0, const Vec3& p1, const color4& color)
{
   int x1=p1.x;
   int y1=p1.y;
   int x0=p0.x;
   int y0=p0.y;

   int dx = abs(x1-x0), sx = x0<x1 ? 1 : -1;
   int dy = abs(y1-y0), sy = y0<y1 ? 1 : -1; 
   int err = dx-dy, e2, x2;                       /* error value e_xy */
   int ed = dx+dy == 0 ? 1 : sqrt((float)dx*dx+(float)dy*dy);

   for ( ; ; ){                                         /* pixel loop */
      DrawPixel(800,600,x0,y0,{color.r,color.g,color.b,color.a});
      e2 = err; x2 = x0;
      if (2*e2 >= -dx) {                                    /* x step */
         if (x0 == x1) break;
         if (e2+dy < ed) DrawPixel(800,600,x0,y0+sy,{color.r,color.g,color.b,color.a});
         err -= dy; x0 += sx; 
      } 
      if (2*e2 <= dy) {                                     /* y step */
         if (y0 == y1) break;
         if (dx-e2 < ed) DrawPixel(800,600,x2+sx,y0, {color.r,color.g,color.b,color.a});
         err += dx; y0 += sy; 
    }
    }
}

Vec3 ndcToScreenCoords(Vec3 ndc, const Viewport& viewport)
{
    ndc.x = ndc.x*viewport.width+(viewport.width/2);
    ndc.y = ndc.y*viewport.height+(viewport.height/2);




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
   
    Vec4 clipCoords[3] = {
        { Vec4{ localCoords[0], 1.f } },
        { Vec4{ localCoords[1], 1.f } },
        { Vec4{ localCoords[2], 1.f } },
    };

    Mat4 translate= translate.CreateTransformMatrix({M_PI,0,0},{400,300,0},{400,400,0});

    clipCoords[0]=translate*clipCoords[0];
    clipCoords[1]=translate*clipCoords[1];
    clipCoords[2]=translate*clipCoords[2];
    
    
     

    
    // Clip space (v4) to NDC (v3)
    // TODO
    Vec3 ndcCoords[3] = {
        { clipCoords[0].x/clipCoords[0].w,clipCoords[0].y/clipCoords[0].w,clipCoords[0].z/clipCoords[0].w },
        {  clipCoords[1].x/clipCoords[1].w,clipCoords[1].y/clipCoords[1].w,clipCoords[1].z/clipCoords[1].w },
        {  clipCoords[2].x/clipCoords[2].w,clipCoords[2].y/clipCoords[2].w,clipCoords[2].z/clipCoords[2].w},
    };



    // NDC (v3) to screen coords (v2)
    // TODO
    Vec3 screenCoords[3] = {
        { ndcToScreenCoords(ndcCoords[0], viewport) },
        { ndcToScreenCoords(ndcCoords[1], viewport) },
        { ndcToScreenCoords(ndcCoords[2], viewport) },
    };


    // Draw triangle wireframe 
    
    DrawLine(ndcCoords[0], ndcCoords[1], lineColor);
    DrawLine(ndcCoords[1], ndcCoords[2], lineColor);
    DrawLine(ndcCoords[0], ndcCoords[2], lineColor); 
    
   DrawLine({0,0,0},{fb->GetWidth(),fb->GetHeight(),0},{0,255,0,1});
}

void Renderer::DrawTriangles(rdrVertex* p_vertices, const uint p_count)
{
    // calculate mvp from matrices
    // Transform vertex list to triangles into colorBuffer
    for (uint i = 0; i < p_count; i += 3)
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
    ImGui::ColorEdit4("lineColor", &lineColor.r);
}
