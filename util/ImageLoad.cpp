#include "ImageLoad.hpp"

#include "util/Util.hpp"
#include "ogl/Texture.hpp"

#include <SDL2/SDL_image.h>

#include <string>

using std::shared_ptr;
using fri::ogl::Texture;

shared_ptr<Texture> fri::LoadImage(const char * FName) {
  SDL_Surface * surface;
  std::string name = fri::GetBaseDirectory();
  name.append(FName);
  surface = IMG_Load(name.c_str());

  auto ret = shared_ptr<Texture>(new Texture());

  if (!surface) {
    std::cerr << "Failed to load image " << FName << " from " << name << std::endl;
    unsigned char * buffer = new unsigned char[256 * 256 * 4];
    for (int x = 0; x < 256; ++x) {
      for (int y = 0; y < 256; ++y) {
        int i = (x + y * 256) * 4;
        buffer[i + 0] = (x +  0) ^ (y +  0);
        buffer[i + 1] = (x +  8) ^ (y +  8);
        buffer[i + 2] = (x + 16) ^ (y + 16);
        buffer[i + 3] = 255; //(x + 32) ^ (y + 32);
      }
    }
    ret->SetTextureData(256, 256, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
    return ret;
  } else {
    SDL_Surface * rgba = SDL_ConvertSurfaceFormat(surface, SDL_PIXELFORMAT_RGBA8888, 0);

    //TODO: we can probably just use the surface data pointer here, but gotta do format lookup
    //and inversion

    int size = rgba->w * rgba->h;
    int source_multiplier = (rgba->format->BitsPerPixel) / 8;
    unsigned char * buffer = new unsigned char[size * 4];
    for (int i = 0; i < size; ++i) {
      // We need to invert Y so do some fancy transforms on the index
      int ai = ((rgba->h - 1 - i / rgba->w) * rgba->w + (i % rgba->w)) * source_multiplier;
      int bi = i * 4;
      buffer[bi + 0] = *(((char*) rgba->pixels) + ai + 3);
      buffer[bi + 1] = *(((char*) rgba->pixels) + ai + 2);
      buffer[bi + 2] = *(((char*) rgba->pixels) + ai + 1);
      buffer[bi + 3] = *(((char*) rgba->pixels) + ai + 0);
    }

    ret->SetTextureData(surface->w, surface->h, GL_RGBA, GL_UNSIGNED_BYTE, buffer);

    SDL_FreeSurface(surface);
    SDL_FreeSurface(rgba);

    delete[] buffer;

    return ret;
  }
}
