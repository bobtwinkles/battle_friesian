#include "flow/GameFlow.hpp"

#include <fstream>

#include <Box2D/Dynamics/b2World.h>

#include "systems/entity/entities/EasyHorse.hpp"
#include "construct/LevelParser.hpp"

using fri::flow::GameFlow;
using fri::flow::IFlow;
using fri::system::GameContext;
using fri::system::input::InputAction;
using fri::system::input::InputResponse;

namespace {
  void JumpHorse(GameContext & Context, const InputAction * Action, std::shared_ptr<fri::system::entity::entities::EasyHorse> H) {
    H->Jump(Context);
  }
}

GameFlow::GameFlow() {
  _debug_draw = std::make_shared<fri::system::render::Box2DDebug>();
  _debug_draw->SetFlags( b2Draw::e_shapeBit
                       | b2Draw::e_jointBit
                       | b2Draw::e_aabbBit
                       | b2Draw::e_pairBit
                       | b2Draw::e_centerOfMassBit);

  b2World & world = _ctx.GetPhysicsSystem().GetWorld();
  world.SetDebugDraw(&(*_debug_draw));
  _debug_draw_index = _ctx.GetRenderSystem().RegisterRenderable(_debug_draw);

  // TODO:
  // ------------------- BEGIN INITIALIZATION HACK --------------------------------
  auto h1 = std::make_shared<fri::system::entity::entities::EasyHorse>(_ctx, 0.3, 0.1);
  _ctx.GetEntitySystem().RegisterGameObject(h1);
  auto h2 = std::make_shared<fri::system::entity::entities::EasyHorse>(_ctx, 0.7, 0.1);
  _ctx.GetEntitySystem().RegisterGameObject(h2);

  fri::system::input::InputSystem & input = _ctx.GetInputSystem();

  input.SetInputMapping(SDLK_SPACE, InputAction::INPUT_JUMP);
  input.SetInputMapping(119       , InputAction::INPUT_UP);
  input.SetInputMapping(97        , InputAction::INPUT_LEFT);
  input.SetInputMapping(115       , InputAction::INPUT_DOWN);
  input.SetInputMapping(100       , InputAction::INPUT_RIGHT);

  input.RegisterInputContinuousTrigger(InputAction::INPUT_JUMP,
      std::bind(JumpHorse, std::placeholders::_1, std::placeholders::_2, h1));
  //--------------------- END  INITIALIZATION HACK --------------------------------

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

void GameFlow::HandleEvent(SDL_Event & Event) {
  switch(Event.type) {
    case SDL_KEYDOWN:
      if (!Event.key.repeat) {
        _ctx.GetInputSystem().InputActivate(_ctx, Event.key.keysym.sym);
      }
      break;
    case SDL_KEYUP:
      if (!Event.key.repeat) {
        _ctx.GetInputSystem().InputDeactivate(_ctx, Event.key.keysym.sym);
      }
      break;
  }
}
