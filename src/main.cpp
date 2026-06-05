#include <iostream>
#include "../include/ConfigParser.hpp"
#include "../include/AssetMapper.hpp"
#include "../include/CodeScanner.hpp"
#include "../include/globals.hpp"

int main(int argc, char* argv[]) {

    ConfigParser parser;
    status = parser.parseArgs(argv);
    if (status == FAILURE) {
        std::cout << parser.getErrorMessage() << "\n\n";
        return 1;
    }
    std::cout<<"\n";

    std::cout << "Searching: " << parser.getSearchableRootDirectory() << "\n";
    std::cout << "Target file extensions: ";
    for (const auto &element : parser.getTargetExtensions()) {
        std::cout << element << " ";
    }
    std::cout << "\n";

    if (status == SUCCESS || status == MISSING_SCAN_EXTENSIONS) {
        std::cout << "Ignored directories: ";
        for (const auto &element : parser.getIgnoredSearchDirectories()) {
            std::cout << element << " ";
        }
        std::cout << "\n";
    }

    if (status == SUCCESS || status == MISSING_IGNORE_DIRECTORIES) {
        std::cout << "Scannable source files: ";
        for (const auto &element : parser.getScannableExtensions()) {
            std::cout << element << " ";
        }
        std::cout << "\n";
    }

    std::cout << "Debug status: " << static_cast<int>(status) << "\n\n";

    AssetMapper* map = nullptr;
    if (status == MISSING_IGNORE_DIRECTORIES || status == MISSING_BOTH) {
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

    CodeScanner* exe = nullptr;
    if (status == SUCCESS) {
        exe = new CodeScanner(parser.getSearchableRootDirectory(), map->getAssets(), parser.getIgnoredSearchDirectories(), parser.getScannableExtensions());
    }
    else if (status == MISSING_IGNORE_DIRECTORIES) {
        exe = new CodeScanner(parser.getSearchableRootDirectory(), map->getAssets(), parser.getScannableExtensions());
    }
    else if (status == MISSING_SCAN_EXTENSIONS) {
        exe = new CodeScanner(parser.getSearchableRootDirectory(), map->getAssets(), parser.getIgnoredSearchDirectories());
    }
    else {
        exe = new CodeScanner(parser.getSearchableRootDirectory(), map->getAssets());
    }
    exe->execute();

    std::cout << "\nBytes Processed: " << exe->getBytesProcessed() << "\n";

    std::cout << "Unreferenced files:\n";
    for (const auto &pair : exe->getLeftoverAssets()) {
        std::cout << pair.first << ": ";
        for (size_t i = 0; i < pair.second.size(); ++i) {
            std::cout << pair.second[i] << " ";
        }
        std::cout << "\n";
    }

    delete map;
    delete exe;
    return 0;
}
