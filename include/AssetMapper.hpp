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
        const std::filesystem::path rootDirectory;
        const std::unordered_set<std::string> targetExtensions;
        const std::unordered_set<std::string> ignoredSearchDirectories;
        bool isValid;

        std::string errorMessage;

    public:
        AssetMapper(std::filesystem::path &rootDirectory, std::unordered_set<std::string> &targetExtensions, std::unordered_set<std::string> &ignoredSearchDirectories);

        bool mapDirectory();

        std::unordered_map<std::string, std::vector<std::filesystem::path>>& getAssets();

        bool isIgnoredDirectory(std::string &directory);

        bool isAnExtension(std::string &extension);

        bool isMapValid();

        void printErrorMessage();

        //std::string extractFilename(std::filesystem::path &path);
};


#endif //STATICTRACE_ASSETMAPPER_H
