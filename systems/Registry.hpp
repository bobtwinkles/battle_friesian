#ifndef _SYSTEM_REGISTRY_H_
#define _SYSTEM_REGISTRY_H_

#include <unordered_map>
#include <string>
#include <limits.h>
#include <type_traits>

#include "util/Util.hpp"
#include "util/ImageLoad.hpp"

namespace fri {
  namespace system {
    namespace animation {
      class Animation;
    }

    //default allocator for registry
    namespace _registry_allocators {
      template<typename T>
      struct DefaultAllocator {
        T operator() (const char * Name) const {
          return T(Name);
        }
      };

      struct TextureAllocator {
        std::shared_ptr<fri::ogl::Texture> operator() (const char * Name) const {
          return fri::LoadImage(Name);
        }
      };
    }

    // T = the type to manage
    // TCreator = a functor that creates a T
    template<typename T, typename TCreator=_registry_allocators::DefaultAllocator<T>>
    class Registry {
      private:
        // Implements FNV-1A for C strings
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
        std::unordered_map<const char *, T, StringHash> _storage;
        TCreator _constructor;

        DISALLOW_COPY_AND_ASSIGN(Registry);
      public:
        Registry() {
        }
        ~Registry() {
        }

        void Register(const char * Key, T & Value) {
          _storage.insert(std::make_pair(Key, Value));
        }

        T Get(const char * Key) {
          auto it = _storage.find(Key);
          if (it == _storage.end()) {
            it = _storage.insert(std::make_pair(Key, _constructor(Key))).first;
          }
          return it->second;
        }
    };

    typedef Registry<animation::Animation> AnimationRegistry;
    typedef Registry<std::shared_ptr<fri::ogl::Texture>, _registry_allocators::TextureAllocator> TextureRegistry;

    AnimationRegistry & GetAnimationRegistry();
    TextureRegistry & GetTextureRegistry();
  }
}

#endif
