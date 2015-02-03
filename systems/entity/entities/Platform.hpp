#ifndef _SYSTEMS_ENTITY_ENTITIES_PLATFORM_H_
#define _SYSTEMS_ENTITY_ENTITIES_PLATFORM_H_

#include "systems/entity/GameObject.hpp"

#include "systems/render/RenderSystem.hpp"
#include "systems/render/renderables/MobileTexturedRender.hpp"

#include "systems/physics/PhysicsObject.hpp"
#include "systems/physics/Fixture.hpp"

namespace fri {
  namespace system {
    namespace entity {
      namespace entities {
        class Platform;

        namespace platform {
          enum PlatformSide {
            TOP, BOTTOM, LEFT, RIGHT
          };

          /**
           * A platform body
           */
          class PlatformBody : public fri::system::physics::PhysicsObject {
            private:
              Platform * _platform;
            public:
              static fri::util::rtti::TypeID _type;

              /**
               * Creates a PlatformBody.
               *
               * Does _not_ manage the Platform passed in.
               *
               * @param World
               * @param Plat The platform for which we are a physics body.
               */
              PlatformBody(b2World & World, Platform * Plat);

              inline Platform * GetPlatform() const { return _platform; }
              virtual ~PlatformBody();
          };

          /**
           * Represents a fixture on a platform.
           *
           * Objects of this class type will represent only one side of the platform.
           * To createa complete platform, this class must be instantiated with sides
           * `PlatformSide::TOP`, `PlatformSide::BOTTOM`, `PlatformSide::RIGHT`, and `PlatformSide::LEFT`.
           */
          class PlatformFixture : public fri::system::physics::Fixture {
            private:
              PlatformSide _side;
            public:
              static fri::util::rtti::TypeID _type;

              /**
               * Create a platform fixture.
               *
               * @param Parent
               * @param W The Width of the platform
               * @param H The Height of the platform
               * @param Side the Side for which we will create
               */
              PlatformFixture(PlatformBody * Parent, PlatformSide Side);

              PlatformSide GetSide() { return _side; }
          };
        }

        /**
         * A static, rectangular platform upon which things can land
         */
        class Platform : public IGameObject {
          private:
            fri::system::render::RenderableIndex _renderable_index;
            platform::PlatformBody * _object;
            float _x, _y, _width, _height;
          public:
            Platform(fri::system::GameContext & Context, float X, float Y, float W, float H, std::shared_ptr<fri::ogl::texture::Texture> Tex);
            ~Platform();

            inline float GetX() const { return _x; }
            inline float GetY() const { return _y; }
            inline float GetWidth() const { return _width; }
            inline float GetHeight() const { return _height; }

            virtual void Tick(fri::system::GameContext & Context, double Step);
        };
      }
    }
  }
}

#endif
