#include "flow/GameFlow.hpp"

#include <fstream>

#include <Box2D/Dynamics/b2World.h>

#include "systems/entity/entities/EasyHorse.hpp"
#include "construct/Parser.hpp"

using fri::flow::GameFlow;
using fri::flow::IFlow;

GameFlow::GameFlow() {
  auto h1 = std::make_shared<fri::system::entity::entities::EasyHorse>(_ctx, 4, 1);
  _ctx.GetEntitySystem().RegisterGameObject(h1);
  auto h2 = std::make_shared<fri::system::entity::entities::EasyHorse>(_ctx, 6, 1);
  _ctx.GetEntitySystem().RegisterGameObject(h2);

  _debug_draw = std::make_shared<fri::system::render::Box2DDebug>();
  _debug_draw->SetFlags(b2Draw::e_shapeBit | b2Draw::e_aabbBit);

  b2World & world = _ctx.GetPhysicsSystem().GetWorld();
  world.SetDebugDraw(&(*_debug_draw));
  _debug_draw_index = _ctx.GetRenderSystem().RegisterRenderable(_debug_draw);

  std::string fname = fri::GetBaseDirectory();
  fname.append("resources/levels/level0.txt");
  std::cout << "Loading level from " << fname << std::endl;
  std::ifstream in(fname);
  fri::construct::ParseLevel(in, _ctx);
}

GameFlow::~GameFlow() {
}

void GameFlow::Tick(double Step) {
  _ctx.Tick(Step);
  b2World & world = _ctx.GetPhysicsSystem().GetWorld();
  world.DrawDebugData();
}

bool GameFlow::ShouldSwitch() {
  return false;
}

IFlow * GameFlow::NextFlow() {
  return nullptr;
}
