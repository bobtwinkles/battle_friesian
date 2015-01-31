#include "systems/physics/Fixture.hpp"

#include <Box2D/Collision/Shapes/b2PolygonShape.h>

#include "systems/physics/PhysicsObject.hpp"

using fri::system::physics::BoxFixture;
using fri::system::physics::Fixture;
using fri::util::rtti::BaseInfo;
using fri::util::rtti::RTTIBase;
using fri::util::rtti::TypeID;

////////////////////////////////////////////////////////////////////////////////
/////////////////////////  Fixture members /////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

Fixture::Fixture (const BaseInfo & Type,
                  PhysicsObject * Parent,
                  b2FixtureDef * Fixture) :
  RTTIBase(Type) {
  _fixture = Parent->GetParent()->CreateFixture(Fixture);
  _fixture->SetUserData(this->GetStub());
}

Fixture::Fixture(const BaseInfo & Type) :
  RTTIBase(Type) {
  _fixture = nullptr;
}

////////////////////////////////////////////////////////////////////////////////
//////////////////////////  BoxFixture members /////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

BoxFixture::BoxFixture(const BaseInfo & Type,
                       PhysicsObject * Parent,
                       float X,
                       float Y,
                       float W,
                       float H) :
  Fixture(Type) {
  Init(Parent, X, Y, W, H);
}

BoxFixture::BoxFixture(const BaseInfo & Type,
                       PhysicsObject * Parent,
                       float W,
                       float H) :
  Fixture(Type) {
  Init(Parent, -(W/2.f), -(H/2.f), W, H);
}

void BoxFixture::Init(PhysicsObject * Parent, float X, float Y, float W, float H) {
  b2FixtureDef def;
  b2PolygonShape box;

  float half_w = W / 2.f
      , half_h = H / 2.f;

  box.SetAsBox(half_w, half_h, b2Vec2(X + half_w, Y + half_h), 0);

  def.shape = &box;
  _fixture = Parent->GetParent()->CreateFixture(&def);
  _fixture->SetUserData(this->GetStub());
}
