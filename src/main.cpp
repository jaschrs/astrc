#include <iostream>
#include "../include/ConfigParser.hpp"
#include "../include/AssetMapper.hpp"
#include "../include/CodeScanner.hpp"

int main(int argc, char* argv[]) {

    ConfigParser parser;
    const ConfigStatus status = parser.parseArgs(argc, argv);
    if (status == FAILURE) {
        std::cout << parser.getErrorMessage() << "\n\n";
        return EXIT_FAILURE;
    }

    std::cout << "\nSearching: " << parser.getSearchableRootDirectory();
    std::cout << "\nTarget file extensions: ";
    for (const auto &element : parser.getTargetExtensions()) {
        std::cout << element << " ";
    }

    std::cout << "\nIgnored directories: ";
    for (const auto &element : parser.getIgnoredSearchDirectories()) {
        std::cout << element << " ";
    }

    std::cout << "\nScannable source files: ";
    for (const auto &element : parser.getScannableExtensions()) {
        std::cout << element << " ";
    }

    std::cout << "\nDebug status: " << static_cast<int>(status) << "\n\n";

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    AssetMapper map(
        parser.getSearchableRootDirectory(),
        parser.getTargetExtensions(),
        parser.getIgnoredSearchDirectories()
        );
    if (map.getAssets().empty()) {
        std::cout << "No assets found\n";
        return EXIT_SUCCESS;
    }
    for (const auto &pair : map.getAssets()) {
        std::cout << pair.first << ": ";
        for (size_t i = 0; i < pair.second.size(); ++i) {
            std::cout << pair.second[i] << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    CodeScanner exe(
        parser.getSearchableRootDirectory(),
        map.getAssets(),
        parser.getIgnoredSearchDirectories(),
        parser.getScannableExtensions()
        );
    exe.execute();

    std::cout << "\nBytes Processed: " << exe.getBytesProcessed() << "\n";

    std::cout << "Unreferenced files:\n";
    for (const auto &pair : exe.getLeftoverAssets()) {
        std::cout << pair.first << ": ";
        for (size_t i = 0; i < pair.second.size(); ++i) {
            std::cout << pair.second[i] << " ";
        }
        std::cout << "\n";
    }

    return EXIT_SUCCESS;
}
