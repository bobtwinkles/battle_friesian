#include "systems/physics/PhysicsObject.hpp"

#include "systems/physics/Fixture.hpp"

using fri::util::rtti::BaseInfo;
using fri::util::rtti::TypeID;
using fri::util::rtti::RTTIBase;
using fri::system::physics::PhysicsObject;

PhysicsObject::PhysicsObject(const BaseInfo & Base) : RTTIBase(Base) {
}

PhysicsObject::~PhysicsObject() {
  for (auto f : _fixtures) {
    delete f;
  }
}

b2Body * PhysicsObject::GetParent() const {
  return _body;
}

void PhysicsObject::AttachFixture(Fixture *  Fix) {
  _fixtures.push_back(Fix);
}
