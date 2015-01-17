#ifndef _UTIL_IMAGELOAD_H_
#define _UTIL_IMAGELOAD_H_

#include <memory>
#include "Texture.hpp"

#include <vector>

namespace fri {
  // The pointer returned through OutData ** must be freed with delete[]
  std::shared_ptr<fri::ogl::Texture> LoadImage(const char * FName);
}

#endif
