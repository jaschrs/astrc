//
// Created by Jasper on 2026-05-19.
//

#include <filesystem>
#include <iostream>
#include "../include/AssetMapper.hpp"

AssetMapper::AssetMapper(std::filesystem::path &rootDirectory, std::unordered_set<std::string> &targetExtensions,
    std::unordered_set<std::string> &ignoredSearchDirectories){

    std::cout << "Mapping static files & ignored specified folders...\n";
    // manual directory iteration
    for (auto iterator = std::filesystem::recursive_directory_iterator(rootDirectory);
        iterator != std::filesystem::recursive_directory_iterator();
        ++iterator) {

        // skip directory if is ignored
        if (iterator->is_directory() && ignoredSearchDirectories.contains(iterator->path().filename().string())) {
            std::cout << "Skipping folder: " << iterator->path().filename().string() << std::endl;
            iterator.disable_recursion_pending();
            continue;
        }

        if (iterator->is_regular_file() && targetExtensions.contains(iterator->path().extension().string()) && iterator->path().filename().string() != "statictraceconfig.json") {
            assets[iterator->path().filename().string()].push_back(iterator->path()); // will create if not existent
        }
    }
}

AssetMapper::AssetMapper(std::filesystem::path &rootDirectory, std::unordered_set<std::string> &targetExtensions) {
    std::cout << "Mapping static files...\n";
    for (const auto &file : std::filesystem::recursive_directory_iterator(rootDirectory)) {
        if (file.is_regular_file() && targetExtensions.contains(file.path().extension().string())) {
            assets[file.path().filename().string()].push_back(file.path()); // will create if not existent
        }
    }
}

std::unordered_map<std::string, std::vector<std::filesystem::path>>& AssetMapper::getAssets() {
    return assets;
}