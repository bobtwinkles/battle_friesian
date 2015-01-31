#ifndef _SYSTEMS_PHYSICS_SYSYEM_H_
#define _SYSTEMS_PHYSICS_SYSYEM_H_

#include <Box2D/Box2D.h>

#include "systems/System.hpp"

#include "systems/physics/PhysicsObject.hpp"

namespace fri {
  namespace system {
    namespace physics {
      class PhysicsSystem : public ISystem {
        private:
          b2World _world;
        public:
          PhysicsSystem();
          ~PhysicsSystem();

          virtual void Tick(fri::system::GameContext & Context, double Step);

          b2World & GetWorld() { return _world; }
      };
    }
  }
}
#endif
