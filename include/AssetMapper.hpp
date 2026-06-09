//
// Created by Jasper on 2026-05-19.
//

#ifndef STATICTRACE_ASSETMAPPER_H
#define STATICTRACE_ASSETMAPPER_H
#include <filesystem>
#include <vector>
#include <unordered_map>
#include <unordered_set>

class AssetMapper {

    private:
        std::unordered_map<std::string, std::vector<std::filesystem::path>> assets;

    public:
        AssetMapper(const std::filesystem::path &rootDirectory,
            const std::unordered_set<std::string> &targetExtensions,
            const std::unordered_set<std::string> &ignoredSearchDirectories);

        const std::unordered_map<std::string, std::vector<std::filesystem::path>>& getAssets() const;
};


#endif //STATICTRACE_ASSETMAPPER_H
