#include "systems/animation/Animation.hpp"

#include <fstream>
#include <iostream>
#include <string>

#include "systems/Registry.hpp"

using fri::system::TextureRegistry;
using fri::system::animation::Animation;

Animation::Animation(const char * FName) {
  std::string name = fri::GetBaseDirectory();
  std::string source_name;
  name.append(FName);
  std::ifstream in(name);
  in >> _num_frames;
  _frames = new std::shared_ptr<fri::ogl::Texture>[_num_frames];
  _frametimes = new int[_num_frames];

  TextureRegistry & reg = fri::system::GetTextureRegistry();

  std::cout << "Reading animation from " << name << std::endl;
  for (int i = 0; i < _num_frames; ++i) {
    in >> _frametimes[i] >> source_name;;
    std::cout << "  " << source_name << " will render for " << _frametimes[i] << " frames" << std::endl;
    _frames[i] = reg.Get(source_name.c_str());
  }
  _current_frame = 0;
  _current_internal_frame = 0;
}

Animation::Animation() {
  _frames = nullptr;
  _frametimes = nullptr;
  _num_frames = 0;
  _current_frame = 0;
  _current_internal_frame = 0;
}

Animation::Animation(const Animation & Other) {
  _num_frames             = Other._num_frames;
  _current_frame          = Other._current_frame;
  _current_internal_frame = Other._current_internal_frame;
  _frames                 = new std::shared_ptr<fri::ogl::Texture>[_num_frames];
  _frametimes             = new int[_num_frames];
  for (int i = 0; i < _num_frames; ++i) {
    _frames[i] = Other._frames[i];
    _frametimes[i] = Other._frametimes[i];
  }
}

Animation::Animation(Animation && Other) {
  _num_frames             = Other._num_frames;
  _current_frame          = Other._current_frame;
  _current_internal_frame = Other._current_internal_frame;
  _frames                 = Other._frames;;
  _frametimes             = Other._frametimes;
  Other._frames     = nullptr;
  Other._frametimes = nullptr;
}

Animation::~Animation() {
  delete[] _frames;
  delete[] _frametimes;
}

Animation & Animation::operator=(Animation && Other) {
  _num_frames             = Other._num_frames;
  _current_frame          = Other._current_frame;
  _current_internal_frame = Other._current_internal_frame;
  _frames                 = Other._frames;;
  _frametimes             = Other._frametimes;
  Other._frames     = nullptr;
  Other._frametimes = nullptr;
  return *this;
}

Animation & Animation::operator=(const Animation & Other) {
  Animation a(Other);
  a.Swap(*this);
  return *this;
}

void Animation::Swap(Animation & Other) {
  std::swap(_frames, Other._frames);
  std::swap(_frametimes, Other._frametimes);
  std::swap(_num_frames, Other._num_frames);
  std::swap(_current_frame, Other._current_frame);
  std::swap(_current_internal_frame, Other._current_internal_frame);
}

void Animation::Randomize() {
  _current_frame = random() % _num_frames;
}

void Animation::Step() {
  ++_current_internal_frame;
  if (_current_internal_frame >= _frametimes[_current_frame]) {
    _current_internal_frame = 0;
    _current_frame = (_current_frame + 1) % _num_frames;
  }
}
