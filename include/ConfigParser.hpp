//
// Created by Jasper on 2026-05-19.
//

#ifndef STATICTRACE_CONFIGPARSES_H
#define STATICTRACE_CONFIGPARSES_H
#include <filesystem>
#include <unordered_set>

class ConfigParser {

    private:
        std::filesystem::path searchableRootDirectory;
        std::unordered_set<std::string> targetExtensions;
        std::unordered_set<std::string> ignoredSearchDirectories;
        bool isValid;

        std::string errorMessage;

    public:
        ConfigParser();

        bool parseArgs(int argc, char* argv[]);

        std::filesystem::path& getSearchableRootDirectory();

        std::unordered_set<std::string>& getTargetExtensions();

        std::unordered_set<std::string>& getIgnoredSearchDirectories();

        bool isConfigValid() const;

        void printErrorMessage();

};


#endif //STATICTRACE_CONFIGPARSES_H
