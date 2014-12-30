#ifndef _OGL_ENVIRONMENT_H_
#define _OGL_ENVIRONMENT_H_

#include "Util.hpp"

#include "Shader.hpp"

namespace fri {
  namespace ogl {
    class Environment {
      private:
        DISALLOW_COPY_AND_ASSIGN(Environment);
        fri::ogl::ShaderProgram * _program;

        int _width, _height;
      public:
        Environment() : _program(NULL), _width(1), _height(1) {}

        inline ShaderProgram * GetCurrentShaderProgram() const { return _program; }

        inline void MakeProgramCurrent(ShaderProgram * Program) {
          _program->Bind();
          _program = Program;
        }
    };
  }
}

#endif
