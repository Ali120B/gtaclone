#include "engine/world/WorldStreamer.hpp"

#include "engine/assets/AssetManager.hpp"

#include <cmath>

namespace open_city {

namespace {
constexpr float kChunkSize = 120.0f;
constexpr int kRadius = 1;
}

void WorldStreamer::initialize(AssetManager* assets, PhysicsSystem* physics) {
    assets_ = assets;
    physics_ = physics;
}

WorldStreamer::ChunkId WorldStreamer::makeChunk(int x, int z) {
    return (static_cast<long long>(x) << 32) | (static_cast<unsigned int>(z));
}

void WorldStreamer::update(const glm::vec3& player_position) {
    const int center_x = static_cast<int>(std::floor(player_position.x / kChunkSize));
    const int center_z = static_cast<int>(std::floor(player_position.z / kChunkSize));

    for (int dx = -kRadius; dx <= kRadius; ++dx) {
        for (int dz = -kRadius; dz <= kRadius; ++dz) {
            const auto id = makeChunk(center_x + dx, center_z + dz);
            if (!loaded_.contains(id)) {
                loaded_.insert(id);
                if (assets_) {
                    assets_->loadModel("chunk_" + std::to_string(id), "world/city_block.glb");
                }
            }
        }
    }
}

} // namespace open_city
