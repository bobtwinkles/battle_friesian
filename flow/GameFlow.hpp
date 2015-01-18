#ifndef _FLOW_GAMEFLOW_H_
#define _FLOW_GAMEFLOW_H_

#include "flow/Flow.hpp"

#include "systems/GameContext.hpp"

namespace fri { 
  namespace flow {
    class GameFlow : public IFlow {
      private:
        fri::system::GameContext _ctx;
      public:
        GameFlow();
        ~GameFlow();

        virtual void Tick(double Step);

        virtual bool ShouldSwitch();
        virtual IFlow * NextFlow();
    };
  }
}

#endif //_FLOW_FLOW_H_
