//
// Created by jay on 13/05/2026.
//

#include "AssetManager.h"

#include <algorithm>

#include "SFML/Graphics/Texture.hpp"

std::map<std::filesystem::path, sf::Texture> AssetManager::textures;

AssetManager::AssetManager() :
rootAssetsFolder("assets"),
texturesFolder("textures") {
    discoverTextures();
}

void AssetManager::discoverTextures() {
    auto files {discoverFiles(rootAssetsFolder / texturesFolder, {".png"}, true)};
    for (const auto& file : files) {
        auto newName {std::filesystem::relative(file, rootAssetsFolder / texturesFolder)};

        textures[newName] = sf::Texture(file.string());
    }
}

sf::Texture *AssetManager::getTexture(const std::filesystem::path &file) {
    if (textures.empty()) {
        throw std::runtime_error("Tried to get a texture, but not are initialised!");
    }
    if (textures.contains(file)) {
        return &textures[file];
    }
    else {
        throw std::runtime_error("Tried to get a texture, but it doesn't exist!");
    }
}

std::vector<std::filesystem::path> AssetManager::discoverFiles(const std::filesystem::path &path, const std::vector<std::string> &extensions, bool recursive) {
    std::vector<std::filesystem::path> files;

    if (recursive) {
        for (const auto& file : std::filesystem::recursive_directory_iterator(path)) {
            if (isValidFile(file, extensions)) {
                files.push_back(file);
            }
        }
    }
    else {
        for (const auto& file : std::filesystem::directory_iterator(path)) {
            if (isValidFile(file, extensions)) {
                files.push_back(file);
            }
        }
    }
    return files;
}

bool AssetManager::isValidFile(const std::filesystem::path &file, const std::vector<std::string> &extensions) {
    if (is_directory(file)) {
        return false;
    }

    if (extensions.empty()) {
        return true;
    }

    if (std::ranges::contains(extensions, file.extension().string())) {
        return true;
    }

    return false;
}
