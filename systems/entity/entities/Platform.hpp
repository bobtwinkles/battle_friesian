#ifndef _SYSTEMS_ENTITY_ENTITIES_PLATFORM_H_
#define _SYSTEMS_ENTITY_ENTITIES_PLATFORM_H_

#include <Box2D/Box2D.h>

#include "systems/entity/GameObject.hpp"

#include "systems/render/RenderSystem.hpp"
#include "systems/render/renderables/MobileTexturedRender.hpp"

namespace fri {
  namespace system {
    namespace entity {
      namespace entities {
        class Platform : public IGameObject {
          private:
            fri::system::render::RenderableIndex _renderable_index;
            b2Body * _body;
          public:
            Platform(fri::system::GameContext & Context, float X, float Y, float W, float H, std::shared_ptr<fri::ogl::Texture> Tex);
            ~Platform();

            virtual void Tick(fri::system::GameContext & Context, double Step);
        };
      }
    }
  }
}

#endif
