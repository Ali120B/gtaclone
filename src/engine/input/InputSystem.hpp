#pragma once

#include <array>

struct GLFWwindow;

namespace open_city {

class InputSystem {
public:
    void initialize(GLFWwindow* window);
    void update();

    [[nodiscard]] bool isDown(int key) const;
    [[nodiscard]] bool wasPressed(int key) const;
    [[nodiscard]] bool isQuitRequested() const;

private:
    GLFWwindow* window_{nullptr};
    std::array<bool, 512> current_{};
    std::array<bool, 512> previous_{};
};

} // namespace open_city
