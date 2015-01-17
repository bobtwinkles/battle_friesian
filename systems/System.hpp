#ifndef _SYSTEM_SYSTEM_H_
#define _SYSTEM_SYSTEM_H_

namespace fri {
  namespace system {
    class GameContext;

    class ISystem {
      private:
      public:
        ISystem () {}
        virtual ~ISystem() {}

        // Step is in seconds
        virtual void Tick (fri::system::GameContext & Context, double Step) = 0;
    };
  }
}

#endif
