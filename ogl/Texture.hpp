#ifndef _OGL_TEXTURE_H_
#define _OGL_TEXTURE_H_

#include <GL/glew.h>
#include "Util.hpp"

namespace fri {
  namespace ogl {
    class Texture {
      private:
        GLuint _texture;

        int _width, _height;

        DISALLOW_COPY_AND_ASSIGN(Texture);
      public:
        Texture();
        ~Texture();

        void SetTextureData(GLsizei Width, GLsizei Height, GLenum Format,
                            GLenum Type, GLvoid * Data);

        void Bind() const { glBindTexture(GL_TEXTURE_2D, _texture); }

        int GetWidth() const { return _width; }
        int GetHeight() const { return _height; }
    };
  }
}

#endif
