#include <iostream>
#include "../include/ConfigParser.hpp"
#include "../include/AssetMapper.hpp"
#include "../include/CodeScanner.hpp"

int main(int argc, char* argv[]) {

    ConfigParser parser;
    ConfigStatus status = parser.parseArgs(argv);
    if (status == ConfigStatus::FAILURE) {
        std::cout << parser.getErrorMessage() << "\n\n";
        return 1;
    }

    std::cout << "Searching: " << parser.getSearchableRootDirectory() << "\n\n";
    std::cout << "Target file extensions: ";
    for (const auto &element : parser.getTargetExtensions()) {
        std::cout << element << " ";
    }
    std::cout << "\n";

    if (status == ConfigStatus::SUCCESS || status == ConfigStatus::MISSING_SCAN_EXTENSIONS) {
        std::cout << "Ignored directories: ";
        for (const auto &element : parser.getIgnoredSearchDirectories()) {
            std::cout << element << " ";
        }
        std::cout << "\n";
    }

    if (status == ConfigStatus::SUCCESS || status == ConfigStatus::MISSING_IGNORE_DIRECTORIES) {
        std::cout << "Scannable source files: ";
        for (const auto &element : parser.getScannableExtensions()) {
            std::cout << element << " ";
        }
        std::cout << "\n";
    }

    std::cout << "Debug status: " << static_cast<int>(status) << "\n\n";

    AssetMapper* map = nullptr;
    if (status == ConfigStatus::MISSING_IGNORE_DIRECTORIES || status == ConfigStatus::MISSING_BOTH) {
        map = new AssetMapper(parser.getSearchableRootDirectory(), parser.getTargetExtensions());
    }
    else {
        map = new AssetMapper(parser.getSearchableRootDirectory(), parser.getTargetExtensions(), parser.getIgnoredSearchDirectories());
    }

    if (map->getAssets().empty()) {
        std::cout << "No assets found\n";
        return 0;
    }
    for (const auto &pair : map->getAssets()) {
        std::cout << pair.first << ": ";
        for (size_t i = 0; i < pair.second.size(); ++i) {
            std::cout << pair.second[i] << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";

    delete map;
    return 0;
}
