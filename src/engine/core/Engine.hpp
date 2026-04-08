#pragma once

#include "engine/assets/AssetManager.hpp"
#include "engine/audio/AudioSystem.hpp"
#include "engine/gameplay/GameWorld.hpp"
#include "engine/input/InputSystem.hpp"
#include "engine/physics/PhysicsSystem.hpp"
#include "engine/render/Renderer.hpp"
#include "engine/world/WorldStreamer.hpp"

#include <memory>

struct GLFWwindow;

namespace open_city {

class Engine {
public:
    bool initialize();
    void run();
    void shutdown();

private:
    void tick(float dt);
    bool setupWindow();

    GLFWwindow* window_{nullptr};
    bool running_{false};

    AssetManager assets_;
    AudioSystem audio_;
    InputSystem input_;
    PhysicsSystem physics_;
    Renderer renderer_;
    WorldStreamer world_streamer_;
    GameWorld game_world_;
};

} // namespace open_city
