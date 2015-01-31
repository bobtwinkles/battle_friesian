#ifndef _SYSTEMS_PHYSICS_FIXTURE_H_
#define _SYSTEMS_PHYSICS_FIXTURE_H_

#include <Box2D/Dynamics/b2Fixture.h>

#include "util/Util.hpp"
#include "util/rtti/RTTIBase.hpp"

namespace fri {
  namespace system {
    namespace physics {
      class PhysicsSystem;
      class PhysicsObject;

      /**
       * Base class of all b2Fixture userdata
       */
      class Fixture : public fri::util::rtti::RTTIBase {
        private:
          DISALLOW_COPY_AND_ASSIGN(Fixture);
        protected:
          b2Fixture * _fixture;
          /**
           * Creates a Fixture without a parent b2Fixture.
           *
           * Only use this constructor if you are implementing a new kind
           * of Fixture. If you are merely a consumer of the PhysicsSystem,
           * use an already extant sub-fixture type as your base clase and
           * go from there..
           *
           *
           * Any implementation that calls this constructor _must_ create
           * and attach the internal `_fixture` itself.
           */
          Fixture(const fri::util::rtti::BaseInfo & BaseInfo);

        public:
          /**
           * Creates a Fixture.
           *
           * @param BaseInfo
           * @param Type The type of fixture we are. Used to determine casting
           * @param Fixture b2FixtureDef describing how the fixture should be created.
           */
          Fixture(const fri::util::rtti::BaseInfo & BaseInfo, PhysicsObject * Parent, b2FixtureDef * Fixture);

          virtual ~Fixture() {}

          inline b2Fixture * GetParent() const { return _fixture; }
      };

      class BoxFixture : public Fixture {
        private:
          void Init(PhysicsObject * Parent, float X, float Y, float W, float H);
        public:
          /**
           * Creates an offset box-shaped fixture.
           *
           * While Box2D operates in (center/radius) coordinates, this constructor
           * operates in (bottom left/diameter) in order to better align with
           * the rest of the engine
           *
           * @param BaseInfo
           * @param X Bottom left X coordinate
           * @param Y Bottom left Y coordinate
           * @param W Width
           * @param H Height
           */
          BoxFixture(const fri::util::rtti::BaseInfo & BaseInfo, PhysicsObject * Parent, float X, float Y, float W, float H);

          /**
           * Creates a box-shaped fixture.
           *
           * This function obeys the Box2D convention of center/radius coordinates
           * because that simply makes the most sense when all we care about is
           * the width and height.
           *
           * @param BaseInfo
           * @param Parent
           * @param W width
           * @param H height
           */
          BoxFixture(const fri::util::rtti::BaseInfo & BaseInfo, PhysicsObject * Parent, float W, float H);
      };
    }
  }
}

#endif
