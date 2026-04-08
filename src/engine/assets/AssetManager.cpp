#include "engine/assets/AssetManager.hpp"

#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <iostream>

namespace open_city {

void AssetManager::initialize(const std::filesystem::path& root) {
    root_ = root;
}

ModelHandle AssetManager::loadModel(const std::string& id, const std::string& relative_path) {
    const auto full_path = resolve(relative_path);
    if (model_cache_.contains(id)) {
        return {id};
    }

    const aiScene* scene = importer_.ReadFile(
        full_path.string(),
        aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_GenNormals | aiProcess_CalcTangentSpace);

    if (!scene || !scene->mRootNode) {
        std::cerr << "Assimp failed to load " << full_path << "\n";
    } else {
        model_cache_[id] = full_path;
    }

    return {id};
}

std::filesystem::path AssetManager::resolve(const std::string& relative_path) const {
    return root_ / relative_path;
}

} // namespace open_city
