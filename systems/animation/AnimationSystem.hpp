#ifndef _SYSTEM_ANIMATION_ANIMATION_SYSTEM_H_
#define _SYSTEM_ANIMATION_ANIMATION_SYSTEM_H_

#include "systems/animation/Animation.hpp"
#include "systems/System.hpp"
#include "systems/Registry.hpp"

#include <list>

namespace fri {
  namespace system {
    namespace animation {
      typedef std::list<Animation*> AnimationList;
      typedef AnimationList::const_iterator AnimationIndex;

      class AnimationSystem : public fri::system::ISystem {
        private:
          AnimationList _animations;
        public:
          AnimationSystem();
          virtual ~AnimationSystem();

          AnimationIndex RegisterAnimation(Animation & Anim);
          void RemoveAnimation(AnimationIndex & Index);

          virtual void Tick (fri::system::GameContext & Context, double Step);
      };
    }
  }
}

#endif
