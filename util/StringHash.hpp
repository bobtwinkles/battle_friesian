#ifndef _UTIL_STRINGHASH_H_
#define _UTIL_STRINGHASH_H_

namespace fri {
  namespace util {
    // Implements FNV-1A for C strings
    // Suitible for use as the Hash parameter to std::unordered_map
    struct StringHash {
      std::size_t operator() (const char * Val) const {
        static_assert(sizeof(std::size_t) * CHAR_BIT == 64, "Expected 64 bit size_t");
        std::size_t hash = 14695981039346656037UL;
        while (*Val != 0) {
          hash = hash ^ *Val;
          hash = hash * 1099511628211L;
          Val++;
        }
        return hash;
      }
    };
  }
}

#endif
