#ifndef _SYSTEM_RENDER_RENDERABLES_MOBILE_TEXTURE_RENDER_H_
#define _SYSTEM_RENDER_RENDERABLES_MOBILE_TEXTURE_RENDER_H_

#include "Renderable.hpp"
#include "Texture.hpp"
#include "TexturedVertexBuffer.hpp"

namespace fri {
  namespace system {
    namespace render {
      class MobileTexturedRenderer : public IRenderable {
        private:
          std::shared_ptr<ogl::Texture> _tex;
          ogl::TexturedVertexBuffer _buffer;
          bool _needs_update;

          float _x, _y;

          void Update();
        public:
          MobileTexturedRenderer(std::shared_ptr<ogl::Texture> Tex);

          MobileTexturedRenderer(const MobileTexturedRenderer & Other);
          MobileTexturedRenderer(const MobileTexturedRenderer && Other);
          MobileTexturedRenderer & operator= (const MobileTexturedRenderer & Other);

          ~MobileTexturedRenderer();

          void SetTexture(std::shared_ptr<ogl::Texture> Tex);
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
