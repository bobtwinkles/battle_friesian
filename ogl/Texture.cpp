#include "ogl/Texture.hpp"

using fri::ogl::Texture;

Texture::Texture() {
  glGenTextures(1, &_texture);

  _width = 0;
  _height = 0;
}

Texture::~Texture() {
  glDeleteTextures(1, &_texture);
}

void Texture::SetTextureData(GLsizei Width, GLsizei Height, GLenum Format,
                             GLenum Type, GLvoid * Data) {
  _width = Width;
  _height = Height;
  glBindTexture(GL_TEXTURE_2D, _texture);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Width, Height, 0, Format, Type, Data);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}
