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
      public:
        Environment() : _program(NULL) {}

        inline ShaderProgram * GetCurrentShaderProgram() const { return _program; }

        inline void MakeProgramCurrent(ShaderProgram * Program) {
          _program = Program;
          _program->Bind();
          _program = Program;
        }
    };
  }
}

#endif
