#ifndef _SYSTEM_RENDER_RENDERABLES_MOBILE_TEXTURE_RENDER_H_
#define _SYSTEM_RENDER_RENDERABLES_MOBILE_TEXTURE_RENDER_H_

#include "ogl/TexturedVertexBuffer.hpp"
#include "ogl/texture/Texture.hpp"
#include "systems/render/Renderable.hpp"

namespace fri {
  namespace system {
    namespace render {
      class MobileTexturedRenderer : public IRenderable {
        private:
          std::shared_ptr<fri::ogl::texture::Texture> _tex;
          ogl::TexturedVertexBuffer _buffer;
          bool _needs_update;

          float _x, _y;

          void Update();
        public:
          MobileTexturedRenderer(std::shared_ptr<fri::ogl::texture::Texture> Tex);

          MobileTexturedRenderer(const MobileTexturedRenderer & Other);
          MobileTexturedRenderer(const MobileTexturedRenderer && Other);
          MobileTexturedRenderer & operator= (const MobileTexturedRenderer & Other);

          ~MobileTexturedRenderer();

          void SetTexture(std::shared_ptr<fri::ogl::texture::Texture> Tex);
          /**
           * Sets the position in screen coordinates of the bottom center of this object
           **/
          void SetPosition(float X, float Y);
          virtual void Render(RenderSystem & System);
      };
    }
  }
}

#endif
