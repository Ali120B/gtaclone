#include "engine/physics/PhysicsSystem.hpp"

#include <BulletCollision/BroadphaseCollision/btDbvtBroadphase.h>
#include <BulletCollision/CollisionDispatch/btCollisionDispatcher.h>
#include <BulletCollision/CollisionDispatch/btDefaultCollisionConfiguration.h>
#include <BulletDynamics/ConstraintSolver/btSequentialImpulseConstraintSolver.h>

namespace open_city {

bool PhysicsSystem::initialize() {
    broadphase_ = std::make_unique<btDbvtBroadphase>();
    collision_configuration_ = std::make_unique<btDefaultCollisionConfiguration>();
    dispatcher_ = std::make_unique<btCollisionDispatcher>(collision_configuration_.get());
    solver_ = std::make_unique<btSequentialImpulseConstraintSolver>();
    world_ = std::make_unique<btDiscreteDynamicsWorld>(dispatcher_.get(), broadphase_.get(), solver_.get(), collision_configuration_.get());
    world_->setGravity(btVector3(0.0f, -9.81f, 0.0f));
    return true;
}

void PhysicsSystem::step(float dt) {
    if (world_) world_->stepSimulation(dt, 8);
}

void PhysicsSystem::shutdown() {
    world_.reset();
    solver_.reset();
    dispatcher_.reset();
    collision_configuration_.reset();
    broadphase_.reset();
}

} // namespace open_city
