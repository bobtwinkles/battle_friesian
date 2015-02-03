#include "ogl/texture/Texture.hpp"

using fri::ogl::texture::Texture;

Texture::Texture() {
  Init(0, 0);
}

Texture::Texture(int W, int H) {
  Init(W, H);
}

void Texture::Init(int W, int H) {
  _width = W;
  _height = H;
}
