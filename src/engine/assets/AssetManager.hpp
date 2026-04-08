#pragma once

#include <assimp/Importer.hpp>
#include <filesystem>
#include <string>
#include <unordered_map>

namespace open_city {

struct ModelHandle {
    std::string id;
};

class AssetManager {
public:
    void initialize(const std::filesystem::path& root);
    ModelHandle loadModel(const std::string& id, const std::string& relative_path);
    [[nodiscard]] std::filesystem::path resolve(const std::string& relative_path) const;

private:
    std::filesystem::path root_;
    std::unordered_map<std::string, std::filesystem::path> model_cache_;
    Assimp::Importer importer_;
};

} // namespace open_city
