#include "systems/render/renderables/Box2DDebug.hpp"

#include <math.h>

#include "systems/Registry.hpp"
#include "systems/Scales.hpp"
#include "systems/render/RenderSystem.hpp"

using fri::system::render::Box2DDebug;
using fri::system::render::RenderSystem;

Box2DDebug::Box2DDebug() :
  _solid_buffer(GL_TRIANGLES, GL_DYNAMIC_DRAW, nullptr),
  _solid_indicies(_solid_buffer.GetIndicies()),
  _solid_vertices(_solid_buffer.GetVertices()),
  _line_buffer(GL_LINES, GL_DYNAMIC_DRAW, nullptr),
  _line_indicies(_line_buffer.GetIndicies()),
  _line_vertices(_line_buffer.GetVertices()) {
  fri::system::TextureRegistry & tex = fri::system::GetTextureRegistry();
  _solid_buffer.SetTexture(tex.Get("WHITE"));
  _line_buffer.SetTexture(tex.Get("WHITE"));
}

Box2DDebug::~Box2DDebug() {
}

void Box2DDebug::Render(RenderSystem & System) {
  glLineWidth(3.f);
  _line_buffer.Sync();
  _line_buffer.Render(System.GetEnvironment());

  _line_indicies.clear();
  _line_vertices.clear();

  _solid_buffer.Sync();
  _solid_buffer.Render(System.GetEnvironment());

  _solid_indicies.clear();
  _solid_vertices.clear();
  glLineWidth(1.f);
}

void Box2DDebug::DrawPolygon(const b2Vec2* Vertices, int32 VertexCount, const b2Color& Color) {
  fri::ogl::TexturedVertex v;
  GLuint base = _line_vertices.size();

  v.u = 1.f;
  v.v = 1.f;
  v.r = Color.r;
  v.g = Color.g;
  v.b = Color.b;
  v.a = Color.a;

  _line_indicies.push_back(base);
  for (auto i = 0; i < VertexCount; ++i) {
    v.x = Vertices[i].x * GFX_SCALE / PHYS_SCALE;
    v.y = Vertices[i].y * GFX_SCALE / PHYS_SCALE;
    _line_vertices.push_back(v);
    _line_indicies.push_back(base + i);
    _line_indicies.push_back(base + i);
  }
  _line_indicies.push_back(base);
}

void Box2DDebug::DrawSolidPolygon(const b2Vec2* Vertices, int32 VertexCount, const b2Color& Color) {
  fri::ogl::TexturedVertex v;
  GLuint base = _solid_vertices.size();

  v.u = 1.f;
  v.v = 1.f;
  v.r = Color.r;
  v.g = Color.g;
  v.b = Color.b;
  v.a = Color.a * 0.5;

  for (auto i = 0; i < VertexCount; ++i) {
    v.x = Vertices[i].x * GFX_SCALE / PHYS_SCALE;
    v.y = Vertices[i].y * GFX_SCALE / PHYS_SCALE;
    _solid_vertices.push_back(v);
    if (0 < i && i < VertexCount - 1) {
      _solid_indicies.push_back(base);
      _solid_indicies.push_back(base + i);
      _solid_indicies.push_back(base + i + 1);
    }
  }

  DrawPolygon(Vertices, VertexCount, Color);
}

#define CIRCLE_ELEMENTS 16

void Box2DDebug::DrawCircle(const b2Vec2 & Center, float32 Radius, const b2Color& Color) {
  float theta;
  fri::ogl::TexturedVertex v;
  GLuint base = _line_vertices.size();

  Radius *= GFX_SCALE / PHYS_SCALE;
  float base_x = Center.x * GFX_SCALE / PHYS_SCALE;
  float base_y = Center.y * GFX_SCALE / PHYS_SCALE;

  v.u = 1.f;
  v.v = 1.f;
  v.r = Color.r;
  v.g = Color.g;
  v.b = Color.b;
  v.a = Color.a;

  for (int i = 0; i < CIRCLE_ELEMENTS; ++i) {
    theta = 2 * M_PI * i / float(CIRCLE_ELEMENTS);
    v.x = base_x + Radius * cosf(theta);
    v.y = base_y + Radius * sinf(theta);
    _line_vertices.push_back(v);
    _line_indicies.push_back(base + i);
    _line_indicies.push_back(base + (i + 1) % CIRCLE_ELEMENTS);
  }
}

void Box2DDebug::DrawSolidCircle(const b2Vec2 & Center, float32 Radius, const b2Vec2 & Axis, const b2Color& Color) {
  float theta;
  fri::ogl::TexturedVertex v;
  GLuint base = _solid_vertices.size();

  Radius *= GFX_SCALE / PHYS_SCALE;
  float base_x = Center.x * GFX_SCALE / PHYS_SCALE;
  float base_y = Center.y * GFX_SCALE / PHYS_SCALE;

  v.x = base_x;
  v.y = base_y;
  v.u = 1.f;
  v.v = 1.f;
  v.r = Color.r;
  v.g = Color.g;
  v.b = Color.b;
  v.a = Color.a * 0.5;

  _solid_vertices.push_back(v);
  for (auto i = 0; i < CIRCLE_ELEMENTS; ++i) {
    theta = 2 * M_PI * i / float(CIRCLE_ELEMENTS);
    v.x = base_x + Radius * cosf(theta);
    v.y = base_y + Radius * sinf(theta);
    _solid_vertices.push_back(v);
    _solid_indicies.push_back(base);
    _solid_indicies.push_back(base + i);
    _solid_indicies.push_back(base + i + 1);
  }

  _solid_indicies.push_back(base);
  _solid_indicies.push_back(base + CIRCLE_ELEMENTS);
  _solid_indicies.push_back(base + 1);

  // border
  DrawCircle(Center, Radius * PHYS_SCALE / GFX_SCALE, Color);
  // pointer
  float scale = (PHYS_SCALE / GFX_SCALE) * Radius / Axis.Length();
  DrawSegment(Center, Center + scale * Axis, Color);
}

void Box2DDebug::DrawSegment(const b2Vec2 & P1, const b2Vec2 & P2, const b2Color& Color) {
  fri::ogl::TexturedVertex v;
  GLuint base = _line_vertices.size();

  v.x = P1.x * GFX_SCALE / PHYS_SCALE;
  v.y = P1.y * GFX_SCALE / PHYS_SCALE;
  v.u = 1.f;
  v.v = 1.f;
  v.r = Color.r;
  v.g = Color.g;
  v.b = Color.b;
  v.a = Color.a;

  _line_vertices.push_back(v);

  v.x = P2.x * GFX_SCALE / PHYS_SCALE;
  v.y = P2.y * GFX_SCALE / PHYS_SCALE;

  _line_vertices.push_back(v);

  _line_indicies.push_back(base + 0);
  _line_indicies.push_back(base + 1);
}

void Box2DDebug::DrawTransform(const b2Transform & Trans) {
  float rot_x = 0.1 * Trans.q.GetXAxis().x;
  float rot_y = 0.1 * Trans.q.GetXAxis().y;
  DrawSolidCircle(Trans.p, 0.1, b2Vec2(rot_x, rot_y), b2Color(1, 1, 1, 1));
}
