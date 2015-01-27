#ifndef _OGL_UI_UI_
#define _OGL_UI_UI_

#include <GL/glew.h>

#include "ogl/Environment.hpp"

namespace fri {
  namespace ogl {
    namespace ui {
      void UIInit();

      // TODO: make this a thing that accepts caps and looks up shader
      fri::ogl::ShaderProgram * GetGraphShader();

      void BeginUIRendering(fri::ogl::Environment & env, int Width, int Height);
      void EndUIRendering();
    }
  }
}

#endif // _OGL_UI_UI_
