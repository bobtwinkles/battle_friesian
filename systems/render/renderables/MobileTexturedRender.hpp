#ifndef _SYSTEM_RENDER_RENDERABLES_MOBILE_TEXTURE_RENDER_H_
#define _SYSTEM_RENDER_RENDERABLES_MOBILE_TEXTURE_RENDER_H_

#include "Renderable.hpp"
#include "Texture.hpp"
#include "TexturedVertexBuffer.hpp"

namespace fri {
  namespace system {
    namespace render {
      class MobileTextureRender : public IRenderable {
        private:
          std::shared_ptr<ogl::Texture> _tex;
          ogl::TexturedVertexBuffer buffer;
        public:
          MobileTextureRender(std::shared_ptr<ogl::Texture> Tex);
          ~MobileTextureRender();

          virtual void Render(RenderSystem & System);
      }
    }
  }
}

#endif
