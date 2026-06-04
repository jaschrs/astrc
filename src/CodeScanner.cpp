//
// Created by Jasper on 2026-05-19.
//

#include "../include/CodeScanner.hpp"
#include <filesystem>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <iostream>
#include "../include/third_party/aho_corasick.hpp"
#include "../include/third_party/mio.hpp"

std::unordered_set<std::string> defaultScannableExtensions = {
    ".html", ".htm", ".css",
    ".scss", ".sass", ".less",
    ".js", ".jsx", ".ts", ".tsx", ".mjs", ".cjs",
    ".vue", ".svelte", ".astro",
    ".cpp", ".hpp", ".c", ".h", ".cs", ".java", ".go", ".rs",
    ".py", ".rb", ".php", ".sh",
    ".json", ".xml", ".csv",
    ".yaml", ".yml", ".toml", ".ini", ".env",
    ".md", ".txt",
    ".swift", ".kt", ".dart", ".xaml",
};

CodeScanner::CodeScanner(std::filesystem::path &searchableRootDirectory, std::unordered_map<std::string, std::vector<std::filesystem::path>> &assets, std::unordered_set<std::string> &ignoredSearchDirectories, std::unordered_set<std::string>& scannableExtensions) :
    searchableRootDirectory(searchableRootDirectory), assets(assets), ignoredSearchDirectories(ignoredSearchDirectories), scannableExtensions(scannableExtensions) {
    bytesProcessed = 0;

    for (const auto &pair : assets) {
        trie.insert(pair.first);
    }
}

void CodeScanner::execute() {
    for (auto iterator = std::filesystem::recursive_directory_iterator(searchableRootDirectory);
        iterator != std::filesystem::recursive_directory_iterator();
        ++iterator) {

        if (iterator->is_directory() && ignoredSearchDirectories.contains(iterator->path().filename().string())) {
            iterator.disable_recursion_pending();
            continue;
        }

        if (iterator->is_regular_file() &&
            defaultScannableExtensions.contains(iterator->path().extension().string()) &&
            std::filesystem::file_size(iterator->path()) > 0 &&
            iterator->path().filename().string() != "statictraceconfig.json") {

            std::cout << "Searching file: " << iterator->path().filename().string() << "\n";

            mio::mmap_source mmap(iterator->path().string());
            std::string buffer = mmap.data();
            auto matches = trie.parse_text(buffer);

            for (const auto &match : matches) {
                std::cout << "Found match: " << match.get_keyword() << "\n";
                assets.erase(match.get_keyword());
            }

            if (assets.empty()) {
                std::cout << "All mapped assets found in source files, none unused!\n";
                break;
            }
            bytesProcessed += mmap.size();
        }
    }
}

std::unordered_map<std::string, std::vector<std::filesystem::path>>& CodeScanner::getLeftoverAssets() {
    return assets;
}

size_t& CodeScanner::getBytesProcessed() {
    return bytesProcessed;
}