#ifndef _SYSTEM_ANIMATION_ANIMATION_SYSTEM_H_
#define _SYSTEM_ANIMATION_ANIMATION_SYSTEM_H_

#include "Animation.hpp"
#include "System.hpp"
#include "Registry.hpp"

#include <list>

namespace fri {
  namespace system {
    namespace animation {
      struct AnimationPointerCreator {
        Animation operator() (const char * Name) const {
          return Animation(Name);
        }
      };

      typedef std::list<Animation*> AnimationList;
      typedef AnimationList::const_iterator AnimationIndex;
      typedef fri::system::Registry<Animation, AnimationPointerCreator> AnimationRegistry;

      class AnimationSystem : public fri::system::ISystem {
        private:
          AnimationList _animations;
          AnimationRegistry _registry;
        public:
          AnimationSystem();
          virtual ~AnimationSystem();

          AnimationIndex RegisterAnimation(Animation & Anim);
          void RemoveAnimation(AnimationIndex & Index);

          virtual void Tick (fri::system::GameContext & Context, double Step);

          AnimationRegistry & GetRegistry() { return _registry; }
      };
    }
  }
}

#endif
