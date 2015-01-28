#ifndef _FLOW_GAMEFLOW_H_
#define _FLOW_GAMEFLOW_H_

#include "flow/Flow.hpp"

#include "systems/GameContext.hpp"
#include "systems/render/RenderSystem.hpp"
#include "systems/render/renderables/Box2DDebug.hpp"

namespace fri {
  namespace flow {
    class GameFlow : public IFlow {
      private:
        fri::system::GameContext _ctx;
        std::shared_ptr<fri::system::render::Box2DDebug> _debug_draw;
        fri::system::render::RenderableIndex _debug_draw_index;
      public:
        GameFlow();
        ~GameFlow();

        virtual void Tick(double Step);

        virtual bool ShouldSwitch();
        virtual IFlow * NextFlow();

        virtual void HandleEvent(SDL_Event & Event);
    };
  }
}

#endif //_FLOW_FLOW_H_
