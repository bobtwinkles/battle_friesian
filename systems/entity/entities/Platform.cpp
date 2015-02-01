#include "systems/entity/entities/Platform.hpp"

#include "systems/GameContext.hpp"
#include "systems/Scales.hpp"
#include "systems/physics/Fixture.hpp"

using fri::ogl::Texture;
using fri::util::rtti::TypeID;
using fri::util::rtti::NextTypeID;
using fri::system::GameContext;
using fri::system::entity::entities::Platform;
using fri::system::entity::entities::platform::PlatformBody;
using fri::system::entity::entities::platform::PlatformFixture;
using fri::system::entity::entities::platform::PlatformSide;
using fri::system::render::MobileTexturedRenderer;

TypeID PlatformBody::_type = NextTypeID();
TypeID PlatformFixture::_type = NextTypeID();

////////////////////////////////////////////////////////////////////////////////
////////////////////////// Main Platform members ///////////////////////////////
////////////////////////////////////////////////////////////////////////////////

Platform::Platform(GameContext & Context, float X, float Y, float W, float H, std::shared_ptr<Texture> Tex) {
  //TODO: implement rendering
  assert(Tex == nullptr);

  b2World & world = Context.GetPhysicsSystem().GetWorld();
  _x = X;
  _y = Y;
  _width = W;
  _height = H;
  _object = new PlatformBody(world, this);

  _object->AttachFixture(new PlatformFixture(_object, PlatformSide::TOP));
  _object->AttachFixture(new PlatformFixture(_object, PlatformSide::BOTTOM));
  _object->AttachFixture(new PlatformFixture(_object, PlatformSide::LEFT));
  _object->AttachFixture(new PlatformFixture(_object, PlatformSide::RIGHT));
}

Platform::~Platform() {
  delete _object;
}

void Platform::Tick(GameContext & Context, double Step) {

}

////////////////////////////////////////////////////////////////////////////////
/////////////////////// Physics Platform members ///////////////////////////////
////////////////////////////////////////////////////////////////////////////////

///////////////////////////// PlatformBody //////////////////////////////////////
PlatformBody::PlatformBody(b2World & World, Platform * Plat) : PhysicsObject( { this, _type} ) {
  _platform = Plat;

  float x = Plat->GetX() * PHYS_SCALE / GFX_SCALE
      , y = Plat->GetY() * PHYS_SCALE / GFX_SCALE
      , w = Plat->GetWidth() * PHYS_SCALE / GFX_SCALE
      , h = Plat->GetHeight() * PHYS_SCALE / GFX_SCALE;

  b2BodyDef def;
  def.type = b2_staticBody;
  def.position.Set((w / 2) + x, (h / 2) + y);
  def.userData = this->GetStub();
  _body = World.CreateBody(&def);
}

PlatformBody::~PlatformBody() {
}

//////////////////////////// PlatformFixture ///////////////////////////////////

PlatformFixture::PlatformFixture(PlatformBody * Parent, PlatformSide Side) : Fixture( {this, _type} ) {
  Platform * plat = Parent->GetPlatform();
  float px = plat->GetX() * PHYS_SCALE / GFX_SCALE
      , py = plat->GetY() * PHYS_SCALE / GFX_SCALE
      , pw = plat->GetWidth() * PHYS_SCALE / GFX_SCALE
      , ph = plat->GetHeight() * PHYS_SCALE / GFX_SCALE;

  float w = pw * 0.1
      , h = ph * 0.1;

  float x, y;
  b2PolygonShape box;

  switch (Side) {
    case PlatformSide::TOP:
      x = 0;
      y = (ph - h) / 2;
      box.SetAsBox(pw / 2, h, b2Vec2(x, y), 0);
      break;
    case PlatformSide::BOTTOM:
      x = 0;
      y = (-ph + h) / 2;
      box.SetAsBox(pw / 2, h, b2Vec2(x, y), 0);
      break;
    case PlatformSide::LEFT:
      x = -pw / 2 + w;
      y = 0;
      box.SetAsBox(w, ph / 2 - h, b2Vec2(x, y), 0);
      break;
    case PlatformSide::RIGHT:
      x = pw / 2 - w;
      y = 0;
      box.SetAsBox(w, ph / 2 - h, b2Vec2(x, y), 0);
      break;
  }


  b2FixtureDef def;
  def.shape = &box;
  def.friction = 0.1;
  def.density = 1;
  def.userData = this->GetStub();

  Parent->GetParent()->CreateFixture(&def);
}
