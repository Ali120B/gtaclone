#include "engine/core/Engine.hpp"

#include <iostream>

int main() {
    open_city::Engine engine;
    if (!engine.initialize()) {
        std::cerr << "Engine initialization failed.\n";
        return 1;
    }

    engine.run();
    engine.shutdown();
    return 0;
}
