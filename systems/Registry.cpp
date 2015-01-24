#include "systems/Registry.hpp"

using fri::system::TextureRegistry;
using fri::system::AnimationRegistry;

#include "systems/animation/Animation.hpp"

namespace {
  AnimationRegistry _animation_registry;
  TextureRegistry _texture_registry;
}

AnimationRegistry & fri::system::GetAnimationRegistry() {
  return _animation_registry;
}

TextureRegistry & fri::system::GetTextureRegistry() {
  return _texture_registry;
}
