#ifndef _OGL_TEXTURE_H_
#define _OGL_TEXTURE_H_

#include <GL/glew.h>
#include "util/Util.hpp"
#include "ogl/Environment.hpp"

namespace fri {
  namespace ogl {
    namespace texture {
      /**
       * Interface representing a texture object
       */
      class Texture {
        private:
          void Init(int W, int H);
        protected:
          /**
           * Width of the texture in graphics units (pixels)
           */
          int _width;
          /**
           * Height of the texutre in graphics units (pixels)
           */
          int _height;
        public:
          /**
           * Create a texture with size 0 by 0
           */
          Texture();
          /**
           * Create a texture with a size
           *
           * @param W width
           * @param H height
           */
          Texture (int W, int H);

          virtual ~Texture() {}

          /**
           * Binds this texture too the GL context and makes it active
           */
          virtual void Bind(Environment & Env) const = 0;

          inline int GetWidth() const { return _width; }
          inline int GetHeight() const { return _height; }
      };
    }
  }
}

#endif
