#include "flow/GameFlow.hpp"

#include "systems/entity/entities/EasyHorse.hpp"

using fri::flow::GameFlow;
using fri::flow::IFlow;

GameFlow::GameFlow() {
  auto h = std::make_shared<fri::system::entity::entities::EasyHorse>(_ctx, 5, 1);
  _ctx.GetEntitySystem().RegisterGameObject(h);
}

GameFlow::~GameFlow() {
}

void GameFlow::Tick(double Step) {
  _ctx.Tick(Step);
}

bool GameFlow::ShouldSwitch() {
  return false;
}

IFlow * GameFlow::NextFlow() {
  return nullptr;
}
