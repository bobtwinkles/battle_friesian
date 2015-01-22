#include "EasyHorse.hpp"

#include "systems/GameContext.hpp"
#include "systems/Scales.hpp"

using fri::system::GameContext;
using fri::system::Registry;
using fri::system::animation::Animation;
using fri::system::animation::AnimationIndex;
using fri::system::animation::AnimationRegistry;
using fri::system::entity::entities::EasyHorse;
using fri::system::render::MobileTexturedRenderer;

EasyHorse::EasyHorse(GameContext & Context, float X, float Y) {
  _animations = new std::shared_ptr<Animation>[2];
  AnimationRegistry & reg = Context.GetAnimationSystem().GetRegistry();
  _animations[0] = reg.Get("resources/animations/level1battlefriesian/canter.anim");;
  _animations[1] = reg.Get("resources/animations/level1battlefriesian/attack1.anim");;
  _current_animation_index = Context.GetAnimationSystem().RegisterAnimation(_animations[0]);

  b2BodyDef def;
  b2World & world = Context.GetPhysicsSystem().GetWorld();
  def.type = b2_dynamicBody;
  def.position.Set(X, Y);
  _body = world.CreateBody(&def);

  b2PolygonShape box;
  float half_phys_w = _animations[0]->GetCurrent()->GetWidth() * PHYS_SCALE / IMG_SCALE / 3
      , half_phys_h = _animations[0]->GetCurrent()->GetHeight() * PHYS_SCALE / IMG_SCALE / 3;
  box.SetAsBox(half_phys_w, half_phys_w, b2Vec2(0, 0), 0);

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
  _renderer->SetPosition(vec.x * GFX_SCALE / PHYS_SCALE,
                         vec.y * GFX_SCALE / PHYS_SCALE);

  // Make sure the renderer has an up-to-date texture
  _renderer->SetTexture((*_current_animation_index)->GetCurrent());
}
