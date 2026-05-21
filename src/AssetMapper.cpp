//
// Created by Jasper on 2026-05-19.
//

#include <filesystem>
#include <iostream>
#include "../include/ConfigParser.hpp"
#include "../include/AssetMapper.hpp"

AssetMapper::AssetMapper(std::filesystem::path &rootDirectory, std::unordered_set<std::string> &targetExtensions,
    std::unordered_set<std::string> &ignoredSearchDirectories) :
    rootDirectory(rootDirectory), targetExtensions(targetExtensions), ignoredSearchDirectories(ignoredSearchDirectories){}

bool mapDirectory() {
    
}

std::unordered_map<std::string, std::vector<std::filesystem::path>>& AssetMapper::getAssets() {
    return assets;
}

bool AssetMapper::isIgnoredDirectory(std::string &directory) {
    return ignoredSearchDirectories.contains(directory);
}

bool AssetMapper::isAnExtension(std::string &extension) {
    return targetExtensions.contains(extension);
}

bool AssetMapper::isMapValid() {
    return isValid;
}

void AssetMapper::printErrorMessage() {
    std::cerr << errorMessage << std::endl;
}
