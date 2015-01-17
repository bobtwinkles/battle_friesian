#include "GameContext.hpp"

using fri::system::GameContext;
using fri::system::animation::AnimationSystem;
using fri::system::render::RenderSystem;

void GameContext::Tick(double Step) {
  _current_time += Step;
  _animation.Tick(*this, Step);
  _render.Tick(*this, Step);
  _entity.Tick(*this, Step);
}
