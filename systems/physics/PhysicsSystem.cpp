#include "systems/physics/PhysicsSystem.hpp"

#include "systems/render/renderables/Box2DDebug.hpp"

using fri::system::GameContext;
using fri::system::physics::PhysicsSystem;

PhysicsSystem::PhysicsSystem() : _world(b2Vec2(0, -9.81)) {
}

PhysicsSystem::~PhysicsSystem() {
}

void PhysicsSystem::Tick(GameContext & Context, double Step) {
  _world.Step(Step, 8, 8);
}
