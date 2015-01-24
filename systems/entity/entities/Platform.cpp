#include "systems/entity/entities/Platform.hpp"

#include "systems/GameContext.hpp"
#include "systems/Scales.hpp"

using fri::ogl::Texture;
using fri::system::GameContext;
using fri::system::entity::entities::Platform;
using fri::system::render::MobileTexturedRenderer;

Platform::Platform(GameContext & Context, float X, float Y, float W, float H, std::shared_ptr<Texture> Tex) {
  //TODO: implement rendering
  assert(Tex == nullptr);

  float half_w = W * PHYS_SCALE / GFX_SCALE / 2;
  float half_h = H * PHYS_SCALE / GFX_SCALE / 2;

  b2BodyDef def;
  b2World & world = Context.GetPhysicsSystem().GetWorld();
  def.type = b2_staticBody;
  def.position.Set(half_w + X * PHYS_SCALE / GFX_SCALE, half_h + Y * PHYS_SCALE / GFX_SCALE);
  _body =world.CreateBody(&def);

  b2PolygonShape box;
  box.SetAsBox(half_w, half_h);

  b2FixtureDef fixture;
  fixture.shape = &box;
  fixture.friction = 0.5f;

  _body->CreateFixture(&fixture);
}

Platform::~Platform() {
}
void Platform::Tick(GameContext & Context, double Step) {
}
