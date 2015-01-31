#ifndef _SYSTEMS_PHYSICS_OBJECT_H_
#define _SYSTEMS_PHYSICS_OBJECT_H_

#include <vector>

#include <Box2D/Dynamics/b2Body.h>
#include <Box2D/Dynamics/b2Fixture.h>

#include "util/Util.hpp"
#include "util/rtti/RTTIBase.hpp"

namespace fri {
  namespace system {
    namespace physics {
      class PhysicsSystem;

      class Fixture;

      /**
       * The base class of all b2Body user data pointers.
       * Should almost never be cast to, as the _type must be determined
       * by the BodyData which comes out of b2Body.GetUserData()
       *
       */
      class PhysicsObject : public fri::util::rtti::RTTIBase {
        private:
          DISALLOW_COPY_AND_ASSIGN(PhysicsObject);

          std::vector<Fixture *> _fixtures;
        protected:
          b2Body * _body;

          /**
           * Creates a PhysicsObject without a b2Body.
           *
           * This constructor is inteded to only be used by subclasses.
           * Any subclass using this constructor instead of one of the public
           * constructors _must_ set the `_body` pointer, and set the userdata
           * of the body to `GetStub()`.
           * it has been filled.
           *
           * @param BaseInfo The RTTI information of the basemost class.
           * @param Type The TypeID of the lowest class in our hierarchy.
           */
          PhysicsObject(const fri::util::rtti::BaseInfo & Type);
        public:
          virtual ~PhysicsObject();

          /**
           * Get the parent object
           *
           * @return The object for which we are userdata
           */
          b2Body * GetParent() const;

          /**
           * Attaches a fixture to this object.
           *
           * Takes responsiblity for `delete`ing the fixture.
           */
          virtual void AttachFixture(Fixture * Fix);
      };
    }
  }
}

#endif
