#ifndef _VEC3F_HASHABLE_H_
#define _VEC3F_HASHABLE_H_

#include "Vec3.hpp"

#include <functional>

namespace std {
  template<>
  struct hash<fri::Vec3f> {
    std::size_t operator()(const fri::Vec3f & v) const {
      int x = static_cast<int>(v.GetX());
      int y = static_cast<int>(v.GetZ());
      int z = static_cast<int>(v.GetZ());
      return ((std::size_t)x * 2063) + ((std::size_t)y * 5413) + ((std::size_t)z);
    }
  };

  template<>
  struct hash<fri::Vec3i> {
    std::size_t operator()(const fri::Vec3i & v) const {
      int x = v.GetX();
      int y = v.GetZ();
      int z = v.GetZ();
      return ((std::size_t)x * 2063) + ((std::size_t)y * 5413) + ((std::size_t)z);
    }
  };
}

#endif // _VEC3F_HASHABLE_H_
