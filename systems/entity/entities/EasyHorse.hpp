#ifndef _SYSTEMS_ENTITY_ENTITIES_EASYHORSE_H_
#define _SYSTEMS_ENTITY_ENTITIES_EASYHORSE_H_

#include <Box2D/Box2D.h>

#include "GameObject.hpp"
#include "AnimationSystem.hpp"
#include "RenderSystem.hpp"

namespace fri {
  namespace system {
    namespace entity {
      namespace entities {
        class EasyHorse : public IGameObject {
          private:
            fri::system::animation::AnimationIndex _current_animation;
            fri::system::render::RenderableIndex _renderable;
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
