#pragma once

#include <glm/vec3.hpp>
#include <memory>
#include <vector>

namespace open_city {

class AssetManager;
class AudioSystem;
class InputSystem;
class PhysicsSystem;
class WorldStreamer;

struct NPC {
    glm::vec3 position{0.0f};
    float waypoint_phase{0.0f};
    int health{100};
};

class GameWorld {
public:
    void initialize(AssetManager* assets, AudioSystem* audio, PhysicsSystem* physics, WorldStreamer* world_streamer);
    void update(float dt, const InputSystem& input);
    void shutdown();

    [[nodiscard]] glm::vec3 playerPosition() const { return player_position_; }
    [[nodiscard]] glm::vec3 cameraPosition() const { return camera_position_; }
    [[nodiscard]] glm::vec3 cameraForward() const { return camera_forward_; }

private:
    void updatePlayer(float dt, const InputSystem& input);
    void updateVehicle(float dt, const InputSystem& input);
    void updateNPCs(float dt);
    void shoot();

    AssetManager* assets_{nullptr};
    AudioSystem* audio_{nullptr};
    PhysicsSystem* physics_{nullptr};
    WorldStreamer* world_streamer_{nullptr};

    glm::vec3 player_position_{0.0f, 3.0f, 0.0f};
    glm::vec3 player_velocity_{0.0f};
    glm::vec3 camera_position_{0.0f, 5.0f, -8.0f};
    glm::vec3 camera_forward_{0.0f, 0.0f, 1.0f};

    bool in_vehicle_{false};
    bool in_main_menu_{true};
    float vehicle_speed_{0.0f};
    float vehicle_heading_{0.0f};
    int player_health_{100};
    int ammo_{120};

    std::vector<NPC> npcs_;
};

} // namespace open_city
