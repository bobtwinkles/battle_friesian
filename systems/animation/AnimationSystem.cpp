#include "AnimationSystem.hpp"

#include "GameContext.hpp"

using fri::system::animation::Animation;
using fri::system::animation::AnimationIndex;
using fri::system::animation::AnimationSystem;

AnimationSystem::AnimationSystem() : ISystem() {
}

AnimationSystem::~AnimationSystem() {
}

void AnimationSystem::Tick(fri::system::GameContext & Context, double step) {
  for (auto e : _animations) {
    e->Step();
  }
}

AnimationIndex AnimationSystem::RegisterAnimation(Animation & Anim) {
  return _animations.insert(_animations.begin(), &Anim);
}

void AnimationSystem::RemoveAnimation(AnimationIndex & Index) {
  _animations.erase(Index);
}
