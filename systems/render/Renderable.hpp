#ifndef _SYSTEMS_RENDER_RENDERABLE_H_
#define _SYSTEMS_RENDER_RENDERABLE_H_

#include <memory>

namespace fri {
  namespace system {
    namespace render {
      class RenderSystem;

      class IRenderable {
        private:
        public:
          IRenderable() {}
          ~IRenderable() {}

          virtual void Render(RenderSystem &) = 0;
      };
    }
  }
}

#endif
