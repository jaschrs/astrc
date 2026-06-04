//
// Created by Jasper on 2026-05-19.
//

#ifndef STATICTRACE_CONFIGPARSES_H
#define STATICTRACE_CONFIGPARSES_H
#include <filesystem>
#include <unordered_set>

enum class ConfigStatus : uint8_t {
    SUCCESS = 0, // found all arguments
    MISSING_SCAN_EXTENSIONS = 1, // only "scanExtensions" key is missing
    MISSING_IGNORE_DIRECTORIES = 2, // only "ignoreDirectories" key is missing
    MISSING_BOTH = 3, // both "scanExtensions" key and "ignoreDirectories" key is missing
    FAILURE = 4 // other failure
};

class ConfigParser {

    private:
        std::filesystem::path searchableRootDirectory;
        std::unordered_set<std::string> targetExtensions;
        std::unordered_set<std::string> ignoredSearchDirectories;
        std::unordered_set<std::string> scannableExtensions;
        ConfigStatus configStatus;
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