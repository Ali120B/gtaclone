#include "engine/input/InputSystem.hpp"

#include <GLFW/glfw3.h>

namespace open_city {

void InputSystem::initialize(GLFWwindow* window) {
    window_ = window;
}

void InputSystem::update() {
    previous_ = current_;
    for (int key = 0; key < 512; ++key) {
        current_[key] = glfwGetKey(window_, key) == GLFW_PRESS;
    }
}

bool InputSystem::isDown(int key) const {
    return key >= 0 && key < static_cast<int>(current_.size()) && current_[key];
}

bool InputSystem::wasPressed(int key) const {
    return key >= 0 && key < static_cast<int>(current_.size()) && current_[key] && !previous_[key];
}

bool InputSystem::isQuitRequested() const {
    return isDown(GLFW_KEY_ESCAPE);
}

} // namespace open_city
