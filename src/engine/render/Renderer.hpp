#pragma once

namespace open_city {

class GameWorld;

class Renderer {
public:
    bool initialize(int width, int height);
    void render(const GameWorld& world);
    void shutdown();
};

} // namespace open_city
