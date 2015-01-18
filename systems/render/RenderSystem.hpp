#ifndef _SYSTEMS_RENDER_RENDERSYSTEM_H_
#define _SYSTEMS_RENDER_RENDERSYSTEM_H_

#include "AnimationSystem.hpp"
#include "Environment.hpp"
#include "Renderable.hpp"
#include "Shader.hpp"
#include "System.hpp"
#include "TexturedVertexBuffer.hpp"
#include "Util.hpp"

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
      };
    }
  }
}

#endif
