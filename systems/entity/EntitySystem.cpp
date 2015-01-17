#include "EntitySystem.hpp"

using fri::system::GameContext;
using fri::system::entity::EntitySystem;
using fri::system::entity::EntityList;
using fri::system::entity::EntityIndex;

EntitySystem::EntitySystem() {
}

EntitySystem::~EntitySystem() {
}

void EntitySystem::Tick(GameContext & Context, double Step) {
  for (auto e : _entites) {
    e->Tick(Context, Step);
  }
}

EntityIndex EntitySystem::RegisterGameObject(std::shared_ptr<IGameObject> GO) {
  return _entites.insert(_entites.begin(), GO);
}

void EntitySystem::RemoveGameObject(EntityIndex Index) {
  _entites.erase(Index);
}
