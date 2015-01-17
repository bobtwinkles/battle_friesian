#ifndef _SYSTEM_GAMECONTEXT_H_
#define _SYSTEM_GAMECONTEXT_H_

#include "Util.hpp"
#include "RenderSystem.hpp"
#include "AnimationSystem.hpp"
#include "EntitySystem.hpp"
#include "PhysicsSystem.hpp"

namespace fri {
  namespace system {
    class GameContext {
      private:
        fri::system::animation::AnimationSystem _animation;
        fri::system::render::RenderSystem _render;
        fri::system::entity::EntitySystem _entity;
        fri::system::physics::PhysicsSystem _physics;
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
