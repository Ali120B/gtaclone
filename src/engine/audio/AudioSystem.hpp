#pragma once

#include <AL/al.h>
#include <AL/alc.h>
#include <glm/vec3.hpp>

namespace open_city {

class AudioSystem {
public:
    bool initialize();
    void updateListener(const glm::vec3& position, const glm::vec3& forward);
    void shutdown();

private:
    ALCdevice* device_{nullptr};
    ALCcontext* context_{nullptr};
};

} // namespace open_city
