#include "engine/render/Renderer.hpp"

#include "engine/gameplay/GameWorld.hpp"

#include <GL/gl.h>

namespace open_city {

bool Renderer::initialize(int, int) {
    glEnable(GL_DEPTH_TEST);
    return true;
}

void Renderer::render(const GameWorld&) {
    glClearColor(0.05f, 0.06f, 0.08f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::shutdown() {}

} // namespace open_city
