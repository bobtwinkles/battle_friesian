#include "EasyHorse.hpp"

#include "systems/GameContext.hpp"

using fri::system::GameContext;
using fri::system::Registry;
using fri::system::animation::Animation;
using fri::system::animation::AnimationIndex;
using fri::system::animation::AnimationRegistry;
using fri::system::entity::entities::EasyHorse;
using fri::system::render::MobileTexturedRenderer;

EasyHorse::EasyHorse(GameContext & Context) {
  _animations = new std::shared_ptr<Animation>[2];
  AnimationRegistry & reg = Context.GetAnimationSystem().GetRegistry();
  _animations[0] = reg.Get("resources/animations/level1battlefriesian/canter.anim");;
  _animations[1] = reg.Get("resources/animations/level1battlefriesian/attack1.anim");;
  _current_animation_index = Context.GetAnimationSystem().RegisterAnimation(_animations[0]);

  b2BodyDef def;
  b2World & world = Context.GetPhysicsSystem().GetWorld();
  def.type = b2_dynamicBody;
  def.position.Set(0.f, 0.f);
  _body = world.CreateBody(&def);

  _renderer = std::make_shared<MobileTexturedRenderer>((*_current_animation_index)->GetCurrent());
  _renderable_index = Context.GetRenderSystem().RegisterRenderable(_renderer);
}

EasyHorse::~EasyHorse() {
  delete[] _animations;
}

void EasyHorse::Tick(GameContext & Context, double Step) {
  _renderer->SetTexture((*_current_animation_index)->GetCurrent());
}
