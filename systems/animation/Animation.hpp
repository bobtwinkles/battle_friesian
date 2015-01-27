#ifndef _SYSTEMS_ANIMATION_ANIMATIN_H_
#define _SYSTEMS_ANIMATION_ANIMATIN_H_

#include <memory>

#include "ogl/Texture.hpp"

namespace fri {
  namespace system {
    namespace animation {
      class Animation {
        private:
          std::shared_ptr<fri::ogl::Texture> * _frames;
          int * _frametimes;
          int _num_frames;
          int _current_frame;
          int _current_internal_frame;
        public:
          Animation();
          Animation(const char * FName);
          Animation(const Animation & Other);
          Animation(Animation && Other);
          ~Animation();

          Animation & operator=(Animation && Other);
          Animation & operator=(const Animation & Other);

          void Swap(Animation & Other);

          // Advance one frame
          void Step();
          // Choose random current frame;
          void Randomize();

          std::shared_ptr<fri::ogl::Texture> GetCurrent() const { return _frames[_current_frame]; }
      };
    }
  }
}

#endif
