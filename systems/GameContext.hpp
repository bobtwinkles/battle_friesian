#ifndef _SYSTEM_GAMECONTEXT_H_
#define _SYSTEM_GAMECONTEXT_H_

#include "util/Util.hpp"
#include "systems/animation/AnimationSystem.hpp"
#include "systems/entity/EntitySystem.hpp"
#include "systems/input/InputSystem.hpp"
#include "systems/physics/PhysicsSystem.hpp"
#include "systems/render/RenderSystem.hpp"

namespace fri {
  namespace system {
    class GameContext {
      private:
        fri::system::animation::AnimationSystem _animation;
        fri::system::render::RenderSystem _render;
        fri::system::entity::EntitySystem _entity;
        fri::system::physics::PhysicsSystem _physics;
        fri::system::input::InputSystem _input;
        double _current_time;

        DISALLOW_COPY_AND_ASSIGN(GameContext);
      public:
        GameContext() { _current_time = 0; }
        ~GameContext() {}

        double GetAspect () { return 9.0 / 16.0; }

        void Tick(double step);

        fri::system::animation::AnimationSystem & GetAnimationSystem() { return _animation; }
        fri::system::render::RenderSystem & GetRenderSystem () { return _render; }
        fri::system::entity::EntitySystem & GetEntitySystem () { return _entity; }
        fri::system::physics::PhysicsSystem & GetPhysicsSystem() { return _physics; }

        double GetCurrentTime() { return _current_time; }
    };
  }
}
#endif
