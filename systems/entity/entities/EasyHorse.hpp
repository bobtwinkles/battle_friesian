#ifndef _SYSTEMS_ENTITY_ENTITIES_EASYHORSE_H_
#define _SYSTEMS_ENTITY_ENTITIES_EASYHORSE_H_

#include <memory>

#include "systems/entity/GameObject.hpp"

#include "systems/animation/AnimationSystem.hpp"

#include "systems/render/RenderSystem.hpp"
#include "systems/render/renderables/MobileTexturedRender.hpp"

#include "systems/physics/PhysicsObject.hpp"

namespace fri {
  namespace system {
    namespace entity {
      namespace entities {
        class EasyHorse : public IGameObject {
          private:
            fri::system::animation::AnimationIndex _current_animation_index;
            fri::system::render::RenderableIndex _renderable_index;
            std::shared_ptr<fri::system::render::MobileTexturedRenderer> _renderer;
            fri::system::animation::Animation * _animations;
            fri::system::physics::PhysicsObject * _object;

            bool _on_ground;
          public:
            /**
             * @param X X in gfx coordinates
             * @param Y Y in gfx coordinates
             */
            EasyHorse(fri::system::GameContext & Context, float X, float Y);
            ~EasyHorse();

            virtual void Tick(fri::system::GameContext & Context, double Step);

            void Jump(fri::system::GameContext & Context);
        };
      }
    }
  }
}

#endif
