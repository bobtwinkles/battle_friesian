#ifndef _PHYSICS_SYSYEM_H_
#define _PHYSICS_SYSYEM_H_

#include "System.hpp"
#include <Box2D/Box2D.h>

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
