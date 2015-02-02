#include "EasyHorse.hpp"

#include "systems/GameContext.hpp"
#include "systems/Scales.hpp"
#include "systems/physics/Fixture.hpp"
#include "systems/physics/PhysicsObject.hpp"

#include "systems/entity/entities/Platform.hpp"

using fri::system::GameContext;
using fri::system::Registry;
using fri::system::AnimationRegistry;
using fri::system::animation::Animation;
using fri::system::animation::AnimationIndex;
using fri::system::entity::entities::EasyHorse;
using fri::system::entity::entities::platform::PlatformFixture;
using fri::system::entity::entities::platform::PlatformSide;
using fri::system::physics::BoxFixture;
using fri::system::physics::PhysicsObject;
using fri::system::physics::PhysicsSystem;
using fri::system::render::MobileTexturedRenderer;
using namespace fri::util::rtti;

namespace {
  /**
   * Implementatino of PhysicsObject for EasyHorse.
   */
  class EasyHorseBody : public PhysicsObject {
    private:
    public:
      static TypeID _type;

      EasyHorseBody(b2World & World, float X, float Y) : PhysicsObject( { this, _type} ) {
        b2BodyDef def;
        def.type = b2_dynamicBody;
        def.position.Set(X, Y);
        _body = World.CreateBody(&def);
        _body->SetUserData(this->GetStub());
      }
  };

  class EasyHorseFixture : public BoxFixture {
    private:
    public:
      static TypeID _type;

      EasyHorseFixture(PhysicsObject * Parent, float W, float H) :
        BoxFixture( {this, _type}, Parent, W, H ) {
        _fixture->SetDensity(1);
        _fixture->SetFriction(0.1f);
      }
  };

  TypeID EasyHorseBody::_type = fri::util::rtti::NextTypeID("EasyHorseBody");
  TypeID EasyHorseFixture::_type = fri::util::rtti::NextTypeID("EasyHorseFixture");
}

EasyHorse::EasyHorse(GameContext & Context, float X, float Y) {
  _animations = new Animation[2];
  AnimationRegistry & reg = fri::system::GetAnimationRegistry();
  _animations[0] = reg.Get("resources/animations/level1battlefriesian/canter.anim");;
  _animations[0].Randomize();
  _animations[1] = reg.Get("resources/animations/level1battlefriesian/attack1.anim");;
  _current_animation_index = Context.GetAnimationSystem().RegisterAnimation(_animations[0]);

  b2World & world = Context.GetPhysicsSystem().GetWorld();
  float phys_w = _animations[0].GetCurrent()->GetWidth() * PHYS_SCALE / IMG_SCALE
      , phys_h = _animations[0].GetCurrent()->GetHeight() * PHYS_SCALE / IMG_SCALE;
  X *= PHYS_SCALE / GFX_SCALE;
  Y *= PHYS_SCALE / GFX_SCALE;

  _object = new EasyHorseBody(world, X, Y);
  _object->AttachFixture(new EasyHorseFixture(_object, phys_w, phys_h));

  _renderer = std::make_shared<MobileTexturedRenderer>((*_current_animation_index)->GetCurrent());
  _renderable_index = Context.GetRenderSystem().RegisterRenderable(_renderer);
  _renderer->SetPosition(X * GFX_SCALE / PHYS_SCALE, Y * GFX_SCALE / PHYS_SCALE);

  _on_ground = true;
}

EasyHorse::~EasyHorse() {
  delete[] _animations;
  delete _object;
}

void EasyHorse::Tick(GameContext & Context, double Step) {
  // Sync position between rendering and physics systems
  b2World & world = Context.GetPhysicsSystem().GetWorld();
  b2Vec2 vec = _object->GetParent()->GetPosition();
  std::shared_ptr<fri::ogl::Texture> t = (*_current_animation_index)->GetCurrent();
  _renderer->SetPosition(vec.x * GFX_SCALE / PHYS_SCALE,
                         vec.y * GFX_SCALE / PHYS_SCALE - (t->GetHeight() * GFX_SCALE / IMG_SCALE / 2));

  // Make sure the renderer has an up-to-date texture
  _renderer->SetTexture(t);

  // assume we have left the ground, but search the contact list for a platform
  // top to verify this claim.
  _on_ground = false;
  b2ContactEdge * contact = _object->GetParent()->GetContactList();
  while (contact) {
    RTTIStub * data = (RTTIStub*) contact->contact->GetFixtureB()->GetUserData();
    PlatformFixture * pf = GetBaseAs<PlatformFixture>(data);
    if (pf) {
      if (pf->GetSide() == PlatformSide::TOP) {
        _on_ground = true;
      }
    }
    contact = contact->next;
  }
}

void EasyHorse::Jump(GameContext & Context) {
  if (_on_ground) {
    b2World & world = Context.GetPhysicsSystem().GetWorld();
    b2Body * body = _object->GetParent();
    b2MassData data;
    body->GetMassData(&data);

    body->ApplyForce(b2Vec2(0, data.mass * 50), data.center, true);
  }
}
