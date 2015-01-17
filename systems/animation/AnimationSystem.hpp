#ifndef _SYSTEM_ANIMATION_ANIMATION_SYSTEM_H_
#define _SYSTEM_ANIMATION_ANIMATION_SYSTEM_H_

#include "Animation.hpp"
#include "System.hpp"
#include "Registry.hpp"

#include <memory>
#include <list>

namespace fri {
  namespace system {
    namespace animation {
      struct AnimationPointerCreator {
        std::shared_ptr<Animation> operator() (const char * Name) const {
          return std::move(std::shared_ptr<Animation>(new Animation(Name)));
        }
      };

      typedef std::list<std::shared_ptr<Animation>> AnimationList;
      typedef AnimationList::const_iterator AnimationIndex;
      typedef fri::system::Registry<std::shared_ptr<Animation>, AnimationPointerCreator> AnimationRegistry;

      class AnimationSystem : public fri::system::ISystem {
        private:
          AnimationList _animations;
          AnimationRegistry _registry;
        public:
          AnimationSystem();
          virtual ~AnimationSystem();

          AnimationIndex RegisterAnimation(std::shared_ptr<Animation> Anim);
          void RemoveAnimation(AnimationIndex & Index);

          virtual void Tick (fri::system::GameContext & Context, double Step);

          AnimationRegistry & GetRegistry() { return _registry; }
      };
    }
  }
}

#endif
