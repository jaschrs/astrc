//
// Created by Jasper on 2026-05-19.
//

#ifndef STATICTRACE_CONFIGPARSES_H
#define STATICTRACE_CONFIGPARSES_H
#include <filesystem>
#include <unordered_set>

enum ConfigStatus : uint8_t {
    SUCCESS = 0, // found all arguments
    MISSING_SCAN_EXTENSIONS = 1, // only "scanExtensions" key is missing
    MISSING_IGNORE_DIRECTORIES = 2, // only "ignoreDirectories" key is missing
    MISSING_BOTH = 3, // both "scanExtensions" key and "ignoreDirectories" key is missing
    FAILURE = 4 // other failure
};

class Parser {

    private:
        std::filesystem::path searchableRootDirectory;
        std::unordered_set<std::string> targetExtensions;
        std::unordered_set<std::string> ignoredSearchDirectories;
        std::unordered_set<std::string> scannableExtensions;
        std::string errorMessage;

        void parseConfigFile(std::ifstream &configFile);

    public:
        Parser();

        ConfigStatus parseArgs(int argc, char* argv[]);

        const std::filesystem::path& getSearchableRootDirectory() const;

        const std::unordered_set<std::string>& getTargetExtensions() const;

        const std::unordered_set<std::string>& getIgnoredSearchDirectories() const;

        const std::unordered_set<std::string>& getScannableExtensions() const;

        const std::string getErrorMessage() const;
};


#endif //STATICTRACE_CONFIGPARSES_H