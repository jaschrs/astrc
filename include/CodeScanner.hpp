//
// Created by Jasper on 2026-05-19.
//

#ifndef STATICTRACE_CODESCANNER_H
#define STATICTRACE_CODESCANNER_H
#include <filesystem>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include "third_party/aho_corasick.hpp"

class CodeScanner {

    private:
        std::filesystem::path searchableRootDirectory;
        std::unordered_map<std::string, std::vector<std::filesystem::path>> assets;
        std::unordered_set<std::string> ignoredSearchDirectories;
        std::unordered_set<std::string> scannableExtensions;
        aho_corasick::trie trie;
        size_t bytesProcessed;

    public:
        CodeScanner(const std::filesystem::path &searchableRootDirectory,
            const std::unordered_map<std::string, std::vector<std::filesystem::path>> &assets,
            const std::unordered_set<std::string> &ignoredSearchDirectories,
            const std::unordered_set<std::string>& scannableExtensions);

        void execute();

        const std::unordered_map<std::string, std::vector<std::filesystem::path>>& getLeftoverAssets() const;

        size_t getBytesProcessed() const;

};


#endif //STATICTRACE_CODESCANNER_H
