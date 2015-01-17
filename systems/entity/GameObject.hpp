#ifndef _SYSTEMS_ENTITY_GAMEOBJECT_H_
#define _SYSTEMS_ENTITY_GAMEOBJECT_H_

namespace fri {
  namespace system {
    class GameContext;

    namespace entity {
      class IGameObject {
        private:
        public:
          IGameObject() {}
          ~IGameObject() {}

          virtual void Tick(fri::system::GameContext & Context, double Step) = 0;
      };
    }
  }
}

#endif
