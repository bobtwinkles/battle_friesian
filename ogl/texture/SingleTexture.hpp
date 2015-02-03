#ifndef _OGL_SINGLETEXTURE_H_
#define _OGL_SINGLETEXTURE_H_

#include "ogl/texture/Texture.hpp"

namespace fri {
  namespace ogl {
    namespace texture {
      /**
       * A Texture which maps conceptual textures 1:1 with OpenGL textures.
       */
      class SingleTexture : public Texture {
        private:
          GLuint _texture;
        public:
          SingleTexture();
          virtual ~SingleTexture();

          void SetTextureData(GLsizei Width, GLsizei Height, GLenum Format,
                              GLenum Type, GLvoid * Data);

          virtual void Bind(Environment & Env) const { glBindTexture(GL_TEXTURE_2D, _texture); }
      };
    }
  }
}

#endif
