//
// Created by Jasper on 2026-05-19.
//

#ifndef STATICTRACE_CONFIGPARSES_H
#define STATICTRACE_CONFIGPARSES_H
#include <filesystem>
#include <unordered_set>
#include "globals.hpp"

class ConfigParser {

    private:
        std::filesystem::path searchableRootDirectory;
        std::unordered_set<std::string> targetExtensions;
        std::unordered_set<std::string> ignoredSearchDirectories;
        std::unordered_set<std::string> scannableExtensions;
        std::string errorMessage;

        void parseConfigFile(std::ifstream &configFile);
        bool verifySubdirectoriesExistence(std::filesystem::path &directory, std::unordered_set<std::string> &set);

    public:
        ConfigParser();

        ConfigStatus parseArgs(char* argv[]);

        std::filesystem::path& getSearchableRootDirectory();

        std::unordered_set<std::string>& getTargetExtensions();

        std::unordered_set<std::string>& getIgnoredSearchDirectories();

        std::unordered_set<std::string>& getScannableExtensions();

        std::string getErrorMessage();
};


#endif //STATICTRACE_CONFIGPARSES_H