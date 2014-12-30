#ifndef _OGL_TEXT_H_
#define _OGL_TEXT_H_

#include "Environment.hpp"

namespace fri {
  namespace ogl {
    namespace ui {
      void TextInit();

      void TextDrawBegin(const fri::ogl::Environment & Env);
      void TextDrawColor(const fri::ogl::Environment & Env, float R, float G, float B);
      void TextDrawString(const fri::ogl::Environment & Env, float X, float Y, const char * String);
      void TextDrawEnd(const fri::ogl::Environment & Env);
    }
  }
}

#endif
