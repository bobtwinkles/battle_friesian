#include "systems/Registry.hpp"

#include "ogl/texture/SingleTexture.hpp"
#include "systems/animation/Animation.hpp"
#include "util/ImageLoad.hpp"

using fri::ogl::texture::SingleTexture;
using fri::ogl::texture::Texture;
using fri::system::AnimationRegistry;
using fri::system::TextureRegistry;
using fri::system::_registry_allocators::TextureAllocator;

namespace {
  AnimationRegistry _animation_registry;
  TextureRegistry _texture_registry;

  void InitTextureRegistry() {
    SingleTexture * white = new SingleTexture();
    float * white_data = new float[64 * 64 * 4];
    for (int i = 0; i < 64 * 64 * 4; ++i) {
      white_data[i] = 1.f;
    }
    white->SetTextureData(64, 64, GL_RGBA, GL_FLOAT, white_data);
    delete[] white_data;

    _texture_registry.Register("WHITE", std::shared_ptr<Texture>(white));
  }
}

std::shared_ptr<fri::ogl::texture::Texture> TextureAllocator::operator() (const char * Name) const {
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
