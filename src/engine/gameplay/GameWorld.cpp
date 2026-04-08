#include "engine/gameplay/GameWorld.hpp"

#include "engine/assets/AssetManager.hpp"
#include "engine/input/InputSystem.hpp"

#include <GLFW/glfw3.h>
#include <algorithm>
#include <cmath>
#include <glm/common.hpp>
#include <glm/geometric.hpp>

namespace open_city {

void GameWorld::initialize(AssetManager* assets, AudioSystem* audio, PhysicsSystem* physics, WorldStreamer* world_streamer) {
    assets_ = assets;
    audio_ = audio;
    physics_ = physics;
    world_streamer_ = world_streamer;

    assets_->loadModel("player", "characters/player_rig.glb");
    assets_->loadModel("vehicle_sedan", "vehicles/sedan.glb");
    assets_->loadModel("vehicle_truck", "vehicles/truck.glb");
    assets_->loadModel("city", "world/city_block.glb");

    for (int i = 0; i < 20; ++i) {
        npcs_.push_back(NPC{glm::vec3(i * 2.5f, 0.0f, std::sin(i) * 10.0f), static_cast<float>(i), 100});
    }
}

void GameWorld::update(float dt, const InputSystem& input) {
    if (in_main_menu_) {
        if (input.wasPressed(GLFW_KEY_ENTER)) {
            in_main_menu_ = false;
        }
        return;
    }

    if (input.wasPressed(GLFW_KEY_M)) {
        in_main_menu_ = true;
        return;
    }

    if (input.wasPressed(GLFW_KEY_E)) {
        in_vehicle_ = !in_vehicle_;
    }

    if (in_vehicle_) {
        updateVehicle(dt, input);
    } else {
        updatePlayer(dt, input);
    }

    if (input.wasPressed(GLFW_KEY_F)) {
        shoot();
    }

    updateNPCs(dt);

    const glm::vec3 target = player_position_ + glm::vec3(0.0f, 2.0f, 0.0f);
    const glm::vec3 desired = target + glm::vec3(-std::sin(vehicle_heading_) * 8.0f, 4.0f, -std::cos(vehicle_heading_) * 8.0f);
    camera_position_ = glm::mix(camera_position_, desired, std::min(1.0f, dt * 6.0f));
    camera_forward_ = glm::normalize(target - camera_position_);
}

void GameWorld::updatePlayer(float dt, const InputSystem& input) {
    glm::vec3 move(0.0f);
    if (input.isDown(GLFW_KEY_W)) move.z += 1.0f;
    if (input.isDown(GLFW_KEY_S)) move.z -= 1.0f;
    if (input.isDown(GLFW_KEY_A)) move.x -= 1.0f;
    if (input.isDown(GLFW_KEY_D)) move.x += 1.0f;

    if (glm::length(move) > 0.001f) {
        move = glm::normalize(move);
    }

    const float speed = input.isDown(GLFW_KEY_LEFT_SHIFT) ? 9.0f : 5.0f;
    player_velocity_.x = move.x * speed;
    player_velocity_.z = move.z * speed;

    if (input.wasPressed(GLFW_KEY_SPACE) && player_position_.y <= 0.05f) {
        player_velocity_.y = 7.0f;
    }

    player_velocity_.y += -9.81f * dt;
    player_position_ += player_velocity_ * dt;

    if (player_position_.y < 0.0f) {
        player_position_.y = 0.0f;
        player_velocity_.y = 0.0f;
    }
}

void GameWorld::updateVehicle(float dt, const InputSystem& input) {
    const float throttle = input.isDown(GLFW_KEY_W) ? 1.0f : 0.0f;
    const float brake = input.isDown(GLFW_KEY_S) ? 1.0f : 0.0f;
    const float steer = (input.isDown(GLFW_KEY_A) ? 1.0f : 0.0f) - (input.isDown(GLFW_KEY_D) ? 1.0f : 0.0f);

    vehicle_speed_ += (throttle * 40.0f - brake * 50.0f - vehicle_speed_ * 1.8f) * dt;
    vehicle_heading_ += steer * dt * 1.2f;

    player_position_.x += std::sin(vehicle_heading_) * vehicle_speed_ * dt;
    player_position_.z += std::cos(vehicle_heading_) * vehicle_speed_ * dt;
}

void GameWorld::shoot() {
    if (ammo_ <= 0) return;
    --ammo_;

    for (auto& npc : npcs_) {
        const glm::vec3 to_npc = npc.position - player_position_;
        if (glm::length(to_npc) < 14.0f) {
            npc.health = std::max(0, npc.health - 40);
            if (npc.health > 0) {
                npc.position += glm::normalize(to_npc) * 5.0f;
            }
        }
    }
}

void GameWorld::updateNPCs(float dt) {
    for (auto& npc : npcs_) {
        if (npc.health <= 0) continue;

        npc.waypoint_phase += dt;
        npc.position.x += std::sin(npc.waypoint_phase) * 0.8f * dt;
        npc.position.z += std::cos(npc.waypoint_phase) * 0.8f * dt;

        const float dist = glm::length(npc.position - player_position_);
        if (dist < 5.0f) {
            const glm::vec3 flee = glm::normalize(npc.position - player_position_);
            npc.position += flee * dt * 5.5f;
        }
    }
}

void GameWorld::shutdown() {
    npcs_.clear();
}

} // namespace open_city
