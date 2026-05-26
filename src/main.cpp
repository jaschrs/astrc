#include <iostream>
#include "../include/ConfigParser.hpp"
#include "../include/AssetMapper.hpp"

int main(int argc, char* argv[]) {

    ConfigParser initializer;
    if (initializer.parseArgs(argc, argv)) {
        std::cout << "Searching: " << initializer.getSearchableRootDirectory() << std::endl;

        std::cout << "Target file extensions: ";
        for (const auto &element : initializer.getTargetExtensions()) {
            std::cout << element << " ";
        }
        std::cout << std::endl;

        std::cout << "Ignored directories: ";
        for (const auto &element : initializer.getIgnoredSearchDirectories()) {
            std::cout << element << " ";
        }
        std::cout << std::endl << std::endl;
    }
    else {
        initializer.printErrorMessage();
        std::cout << std::endl;
        exit(1);
    }

    AssetMapper map(initializer.getSearchableRootDirectory(), initializer.getTargetExtensions(), initializer.getIgnoredSearchDirectories());
    map.mapDirectory();
    for (const auto &pair : map.getAssets()) {
        std::cout << pair.first << ": ";
        for (size_t i = 0; i < pair.second.size(); ++i) {
            std::cout << pair.second[i] << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
