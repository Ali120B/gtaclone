#pragma once

#include <glm/vec3.hpp>
#include <unordered_set>

namespace open_city {

class AssetManager;
class PhysicsSystem;

class WorldStreamer {
public:
    void initialize(AssetManager* assets, PhysicsSystem* physics);
    void update(const glm::vec3& player_position);

private:
    using ChunkId = long long;
    static ChunkId makeChunk(int x, int z);

    AssetManager* assets_{nullptr};
    PhysicsSystem* physics_{nullptr};
    std::unordered_set<ChunkId> loaded_;
};

} // namespace open_city
