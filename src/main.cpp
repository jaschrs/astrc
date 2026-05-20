#include <iostream>
#include "../include/ConfigParser.hpp"

int main(int argc, char* argv[]) {

    ConfigParser initializer;
    bool canContinue = initializer.parseArgs(argc, argv);

    if (canContinue) {
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
    }

    return 0;
}
