#ifndef _SYSTEMS_ENTITY_ENTITIES_EASYHORSE_H_
#define _SYSTEMS_ENTITY_ENTITIES_EASYHORSE_H_

#include <Box2D/Box2D.h>
#include <memory>

#include "systems/entity/GameObject.hpp"

#include "systems/animation/AnimationSystem.hpp"

#include "systems/render/RenderSystem.hpp"
#include "systems/render/renderables/MobileTexturedRender.hpp"

namespace fri {
  namespace system {
    namespace entity {
      namespace entities {
        class EasyHorse : public IGameObject {
          private:
            fri::system::animation::AnimationIndex _current_animation_index;
            fri::system::render::RenderableIndex _renderable_index;
            std::shared_ptr<fri::system::render::MobileTexturedRenderer> _renderer;
            std::shared_ptr<fri::system::animation::Animation> * _animations;
            b2Body * _body;
          public:
            EasyHorse(fri::system::GameContext & Context);
            ~EasyHorse();

            virtual void Tick(fri::system::GameContext & Context, double Step);
        };
      }
    }
  }
}

#endif
