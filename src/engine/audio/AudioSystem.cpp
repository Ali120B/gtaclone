#include "engine/audio/AudioSystem.hpp"

#include <iostream>

namespace open_city {

bool AudioSystem::initialize() {
    device_ = alcOpenDevice(nullptr);
    if (!device_) return false;

    context_ = alcCreateContext(device_, nullptr);
    if (!context_ || !alcMakeContextCurrent(context_)) {
        std::cerr << "Failed to create OpenAL context\n";
        return false;
    }
    return true;
}

void AudioSystem::updateListener(const glm::vec3& position, const glm::vec3& forward) {
    const ALfloat orientation[] = {forward.x, forward.y, forward.z, 0.0f, 1.0f, 0.0f};
    alListener3f(AL_POSITION, position.x, position.y, position.z);
    alListenerfv(AL_ORIENTATION, orientation);
}

void AudioSystem::shutdown() {
    if (context_) {
        alcMakeContextCurrent(nullptr);
        alcDestroyContext(context_);
        context_ = nullptr;
    }
    if (device_) {
        alcCloseDevice(device_);
        device_ = nullptr;
    }
}

} // namespace open_city
