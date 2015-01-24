#ifndef _CONSTRUCT_LEVELPARSER_H_
#define _CONSTRUCT_LEVELPARSER_H_

#include <istream>
#include "systems/GameContext.hpp"

namespace fri {
  namespace construct {
    void ParseLevel(std::istream & Input, fri::system::GameContext & Context);
  }
}

#endif
