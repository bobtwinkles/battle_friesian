#ifndef _UTIL_STRINGHASH_H_
#define _UTIL_STRINGHASH_H_

#include <type_traits>
#include <cstddef>
#include <climits>

static_assert(sizeof(std::size_t) * CHAR_BIT == 64, "Expected 64 bit size_t");

namespace fri {
  namespace util {
    // Implements FNV-1A for C strings
    // Suitible for use as the Hash parameter to std::unordered_map
    template<typename T>
    struct NullTerminatedHash {
      std::size_t operator() (T * Val) const {
        std::size_t hash = 14695981039346656037UL;
        while (*Val != 0) {
          hash = hash ^ *Val;
          hash = hash * 1099511628211L;
          Val++;
        }
        return hash;
      }
    };

    // Specialization convinence for C strings
    struct StringHash : public NullTerminatedHash<const char> {};

    // Implements FNV-1A for general objects
    // Suitible for use as the Hash parameter to std::unordered_map
    template<typename T>
    struct FNVHash {
      std::size_t operator() (const T & Val) const {
        std::size_t hash = 14695981039346656037UL;
        // unsafe cast, but since we're doing a bytewise hash it should be OK
        char * data = (char*)(&Val);
        for (auto i = 0; i < sizeof(T); ++i) {
          hash = hash ^ (data[i]);
          hash = hash * 1099511628211L;
        }
        return hash;
      }
    };
  }
}

#endif
