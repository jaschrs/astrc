#include <iostream>
#include "../include/ConfigParser.hpp"
#include "../include/AssetMapper.hpp"

int main(int argc, char* argv[]) {

    ConfigParser initializer;
    if (initializer.parseArgs(argc, argv)) {
        for (const auto &element : initializer.getIgnoredSearchDirectories()) {
            std::cout << element << " ";
        }
        std::cout << std::endl;

        for (const auto &element : initializer.getTargetExtensions()) {
            std::cout << element << " ";
        }
        std::cout << std::endl;

        std::cout << initializer.getSearchableRootDirectory() << std::endl;
        std::cout << std::endl;
    }
    else {
        initializer.printErrorMessage();
        std::cout << std::endl;
        exit(1);
    }

    AssetMapper map(initializer.getSearchableRootDirectory(), initializer.getTargetExtensions(), initializer.getIgnoredSearchDirectories());

    return 0;
}
