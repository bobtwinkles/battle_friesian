#include "systems/Registry.hpp"

using fri::system::TextureRegistry;
using fri::system::AnimationRegistry;
using fri::system::_registry_allocators::TextureAllocator;

#include "util/ImageLoad.hpp"
#include "systems/animation/Animation.hpp"

namespace {
  AnimationRegistry _animation_registry;
  TextureRegistry _texture_registry;

  void InitTextureRegistry() {
    auto white = std::make_shared<fri::ogl::Texture>();
    float * white_data = new float[64 * 64 * 4];
    for (int i = 0; i < 64 * 64 * 4; ++i) {
      white_data[i] = 1.f;
    }
    white->SetTextureData(64, 64, GL_RGBA, GL_FLOAT, white_data);
    delete[] white_data;

    _texture_registry.Register("WHITE", white);
  }
}

std::shared_ptr<fri::ogl::Texture> TextureAllocator::operator() (const char * Name) const {
  return fri::LoadImage(Name);
}

AnimationRegistry & fri::system::GetAnimationRegistry() {
  return _animation_registry;
}

TextureRegistry & fri::system::GetTextureRegistry() {
  return _texture_registry;
}

void fri::system::InitRegistries() {
  InitTextureRegistry();
}
