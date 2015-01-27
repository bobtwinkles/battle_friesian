#ifndef _SYSTEMS_ENTITY_ENTITYSYSTEM_H_
#define _SYSTEMS_ENTITY_ENTITYSYSTEM_H_

#include "systems/System.hpp"
#include "systems/entity/GameObject.hpp"

#include <list>
#include <memory>

namespace fri {
  namespace system {
    namespace entity {
      typedef std::list<std::shared_ptr<IGameObject>> EntityList;
      typedef EntityList::iterator EntityIndex;

      class EntitySystem : ISystem {
        private:
          EntityList _entites;
        public:
          EntitySystem();
          ~EntitySystem();

          virtual void Tick(fri::system::GameContext & Contex, double Step);

          EntityIndex RegisterGameObject(std::shared_ptr<IGameObject> GO);
          void RemoveGameObject(EntityIndex Index);
      };
    }
  }
}
#endif
