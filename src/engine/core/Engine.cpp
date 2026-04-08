#include "engine/core/Engine.hpp"

#include <GLFW/glfw3.h>
#include <iostream>

namespace open_city {

namespace {
constexpr int kWindowWidth = 1600;
constexpr int kWindowHeight = 900;
}

bool Engine::setupWindow() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window_ = glfwCreateWindow(kWindowWidth, kWindowHeight, "Open City Clone", nullptr, nullptr);
    if (!window_) {
        std::cerr << "Failed to create window\n";
        return false;
    }

    glfwMakeContextCurrent(window_);
    glfwSwapInterval(1);
    return true;
}

bool Engine::initialize() {
    if (!setupWindow()) return false;

    input_.initialize(window_);
    assets_.initialize("assets");
    audio_.initialize();
    physics_.initialize();
    renderer_.initialize(kWindowWidth, kWindowHeight);
    world_streamer_.initialize(&assets_, &physics_);
    game_world_.initialize(&assets_, &audio_, &physics_, &world_streamer_);

    running_ = true;
    return true;
}

void Engine::run() {
    double previous_time = glfwGetTime();
    while (running_ && !glfwWindowShouldClose(window_)) {
        const double now = glfwGetTime();
        const float dt = static_cast<float>(now - previous_time);
        previous_time = now;

        glfwPollEvents();
        if (input_.isQuitRequested()) running_ = false;
        tick(dt);
        glfwSwapBuffers(window_);
    }
}

void Engine::tick(float dt) {
    input_.update();
    game_world_.update(dt, input_);
    physics_.step(dt);
    world_streamer_.update(game_world_.playerPosition());
    audio_.updateListener(game_world_.cameraPosition(), game_world_.cameraForward());
    renderer_.render(game_world_);
}

void Engine::shutdown() {
    game_world_.shutdown();
    audio_.shutdown();
    physics_.shutdown();
    renderer_.shutdown();

    if (window_) {
        glfwDestroyWindow(window_);
        window_ = nullptr;
    }
    glfwTerminate();
}

} // namespace open_city
