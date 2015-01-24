#include "EasyHorse.hpp"

#include "systems/GameContext.hpp"
#include "systems/Scales.hpp"

using fri::system::GameContext;
using fri::system::Registry;
using fri::system::AnimationRegistry;
using fri::system::animation::Animation;
using fri::system::animation::AnimationIndex;
using fri::system::entity::entities::EasyHorse;
using fri::system::render::MobileTexturedRenderer;

EasyHorse::EasyHorse(GameContext & Context, float X, float Y) {
  _animations = new Animation[2];
  AnimationRegistry & reg = fri::system::GetAnimationRegistry();
  _animations[0] = reg.Get("resources/animations/level1battlefriesian/canter.anim");;
  _animations[0].Randomize();
  _animations[1] = reg.Get("resources/animations/level1battlefriesian/attack1.anim");;
  _current_animation_index = Context.GetAnimationSystem().RegisterAnimation(_animations[0]);

  b2BodyDef def;
  b2World & world = Context.GetPhysicsSystem().GetWorld();
  def.type = b2_dynamicBody;
  def.position.Set(X, Y);
  _body = world.CreateBody(&def);

  b2PolygonShape box;
  float half_phys_w = _animations[0].GetCurrent()->GetWidth() * PHYS_SCALE / IMG_SCALE / 2
      , half_phys_h = _animations[0].GetCurrent()->GetHeight() * PHYS_SCALE / IMG_SCALE / 2;
  box.SetAsBox(half_phys_w, half_phys_h, b2Vec2(0, 0), 0);

  b2FixtureDef fixture;
  fixture.shape = &box;
  fixture.density = 1;
  fixture.friction = 0.3f;

  _body->CreateFixture(&fixture);

  _renderer = std::make_shared<MobileTexturedRenderer>((*_current_animation_index)->GetCurrent());
  _renderable_index = Context.GetRenderSystem().RegisterRenderable(_renderer);
  _renderer->SetPosition(X * GFX_SCALE / PHYS_SCALE, Y * GFX_SCALE / PHYS_SCALE);

  _temp = 1;
}

EasyHorse::~EasyHorse() {
  delete[] _animations;
}

void EasyHorse::Tick(GameContext & Context, double Step) {
  // Sync position between rendering and physics systems
  b2World & world = Context.GetPhysicsSystem().GetWorld();
  b2Vec2 vec = _body->GetPosition();
  std::shared_ptr<fri::ogl::Texture> t = (*_current_animation_index)->GetCurrent();
  _renderer->SetPosition(vec.x * GFX_SCALE / PHYS_SCALE,
                         vec.y * GFX_SCALE / PHYS_SCALE - (t->GetHeight() * GFX_SCALE / IMG_SCALE / 2));

  // Make sure the renderer has an up-to-date texture
  _renderer->SetTexture(t);
}
