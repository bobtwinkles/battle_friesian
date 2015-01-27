#ifndef _SYSTEMS_RENDER_RENDERSYSTEM_H_
#define _SYSTEMS_RENDER_RENDERSYSTEM_H_

#include "ogl/Environment.hpp"
#include "ogl/Shader.hpp"
#include "ogl/TexturedVertexBuffer.hpp"
#include "systems/System.hpp"
#include "systems/animation/Animation.hpp"
#include "systems/render/Renderable.hpp"
#include "util/Util.hpp"

#include <memory>
#include <list>

namespace fri {
  namespace system {
    namespace render {
      typedef std::list<std::shared_ptr<IRenderable>>::iterator RenderableIndex;

      class RenderSystem : fri::system::ISystem {
        private:
          fri::ogl::ShaderProgram * _prog;
          fri::ogl::Environment * _env;
          fri::ogl::TexturedVertexBuffer * _bg;

          std::list<std::shared_ptr<IRenderable>> _renderables;

          DISALLOW_COPY_AND_ASSIGN(RenderSystem);
        public:
          RenderSystem();
          ~RenderSystem();

          RenderableIndex RegisterRenderable(std::shared_ptr<IRenderable> Ren);
          void RemoveRenderable(RenderableIndex & Index);

          fri::ogl::Environment & GetEnvironment() { return * _env; }

          virtual void Tick (fri::system::GameContext & Context, double Step);

          void SetBackgroundTexture(std::shared_ptr<fri::ogl::Texture>);
      };
    }
  }
}

#endif
