#pragma once

#include <BulletDynamics/Dynamics/btDiscreteDynamicsWorld.h>
#include <LinearMath/btDefaultMotionState.h>
#include <memory>

namespace open_city {

class PhysicsSystem {
public:
    bool initialize();
    void step(float dt);
    void shutdown();

    [[nodiscard]] btDiscreteDynamicsWorld* world() const { return world_.get(); }

private:
    std::unique_ptr<btBroadphaseInterface> broadphase_;
    std::unique_ptr<btDefaultCollisionConfiguration> collision_configuration_;
    std::unique_ptr<btCollisionDispatcher> dispatcher_;
    std::unique_ptr<btSequentialImpulseConstraintSolver> solver_;
    std::unique_ptr<btDiscreteDynamicsWorld> world_;
};

} // namespace open_city
