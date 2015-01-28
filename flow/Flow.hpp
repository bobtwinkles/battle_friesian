#ifndef _FLOW_FLOW_H_
#define _FLOW_FLOW_H_

#include <SDL2/SDL_events.h>

#include "util/Util.hpp"

namespace fri {
  namespace flow {
    class IFlow {
      private:

      public:
        IFlow() {}
        ~IFlow() {}

        virtual void Tick(double Step) = 0;

        virtual bool ShouldSwitch() = 0;
        virtual IFlow * NextFlow() = 0;

        virtual void HandleEvent(SDL_Event & Event) = 0;
    };
  }
}

#endif // _FLOW_FLOW_H_
