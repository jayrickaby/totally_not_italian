//
// Created by jay on 13/05/2026.
//

#ifndef TOTALLY_NOT_ITALIAN_ASSETMANAGER_H
#define TOTALLY_NOT_ITALIAN_ASSETMANAGER_H
#include <filesystem>
#include <map>
#include <vector>


namespace sf {
    class Texture;
}

class AssetManager {
public:
    AssetManager();

    // Getters
    static sf::Texture* getTexture(const std::filesystem::path& file);

private:
    // Asset Locating
    const std::filesystem::path rootAssetsFolder;
    const std::filesystem::path texturesFolder;

    std::vector<std::filesystem::path> discoverFiles(const std::filesystem::path& path,
                                                     const std::vector<std::string>& extensions,
                                                     bool recursive
                                                     );

    bool isValidFile(const std::filesystem::path& file, const std::vector<std::string>& extensions);

    // Asset Storing
    void discoverTextures();
    static std::map<std::filesystem::path, sf::Texture> textures;
};



#endif //TOTALLY_NOT_ITALIAN_ASSETMANAGER_H
