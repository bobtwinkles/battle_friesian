#ifndef _UTIL_IMAGELOAD_H_
#define _UTIL_IMAGELOAD_H_

#include <memory>

#include <vector>

namespace fri {
  namespace ogl {
    namespace texture {
      class Texture;
    }
  }
  // The pointer returned through OutData ** must be freed with delete[]
  std::shared_ptr<fri::ogl::texture::Texture> LoadImage(const char * FName);
}

#endif
