#include "systems/render/renderables/MobileTexturedRender.hpp"

#include <GL/glew.h>

#include "systems/Scales.hpp"
#include "systems/render/RenderSystem.hpp"

using fri::ogl::Texture;
using fri::ogl::TexturedVertexBuffer;
using fri::system::render::MobileTexturedRenderer;

MobileTexturedRenderer::MobileTexturedRenderer(std::shared_ptr<ogl::Texture> Tex) :
  _buffer(GL_TRIANGLE_STRIP, GL_STATIC_DRAW, Tex) {
  _tex = Tex;
  _needs_update = true;
  _x = 0;
  _y = 0;
}

MobileTexturedRenderer::~MobileTexturedRenderer() {
}

void MobileTexturedRenderer::Render(RenderSystem & System) {
  if (_needs_update) {
    Update();
  }

  _buffer.Render(System.GetEnvironment());
}

void MobileTexturedRenderer::Update() {
  float w = _tex->GetWidth() * GFX_SCALE / IMG_SCALE;
  float h = _tex->GetHeight() * GFX_SCALE / IMG_SCALE;

  float min_x = _x - w / 2;
  float min_y = _y;

  //TODO: Make a fast path for modifying this data in-place<Plug>delimitMateCR
  _buffer.ClearVertexData();
  fri::ogl::QueueTexturedRectangle(_buffer, glm::vec2(min_x, min_y), glm::vec2(min_x + w, min_y + h),
                                            glm::vec2(0, 0), glm::vec2(1, 1));

  _buffer.Sync();

  _needs_update = false;
}

void MobileTexturedRenderer::SetTexture(std::shared_ptr<Texture> Tex) {
  _tex = Tex;
  _buffer.SetTexture(Tex);
  _needs_update = true;
}

void MobileTexturedRenderer::SetPosition(float X, float Y) {
  _x = X;
  _y = Y;
}
