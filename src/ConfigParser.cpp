//
// Created by Jasper on 2026-05-19.
//

#include "../include/ConfigParser.hpp"
#include <string>
#include <iostream>

namespace {

    void parseRespectively(std::string &arg, std::unordered_set<std::string> &set) {
        size_t start = 0;
        while (start < arg.size()) {
            size_t end = arg.find(',', start);
            if (end == std::string_view::npos) {
                end = arg.size();
            }

            set.insert(arg.substr(start, end - start));

            start = end + 1;
        }
    }

    bool verifySubdirectoriesExistence( std::filesystem::path &directory, std::unordered_set<std::string> &set) {
        for (const auto &subdirectory : set) {
            if (!std::filesystem::is_directory(directory.generic_string() + subdirectory)) {
                return false;
            }
        }
        return true;
    }

}

bool ConfigParser::parseArgs(int argc, char* argv[]) {

    bool ignoringNextArg = false;

    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];

        if (ignoringNextArg) {
            parseRespectively(arg, ignoredSearchDirectories);
            ignoringNextArg = false;
            continue;
        }

        if (arg == "-h" || arg == "--help") {
            std::cerr << "Usage: StaticTrace <DIRECTORY> <EXTENSIONS> [CONFIG...]" << std::endl;
            std::cerr << std::endl;
            std::cerr << "Configurations:" << std::endl;
            std::cerr << std::endl;
            std::cerr << "\t-h, --help\tPrint this help message" << std::endl;
            std::cerr << std::endl;
            std::cerr << "\t-v, --version\tPrint version number" << std::endl;
            std::cerr << std::endl;
            std::cerr << "\t-i, --ignore\tDirectories in specified to ignore search" << std::endl;
            std::cerr << std::endl;
            std::cerr << "\tExample: \tStaticTrace ./MyProject \"png,jsx\" --ignore \".vscode,node_modules\"" << std::endl;
            return isConfigValid();
        }
        if (arg == "-v" || arg == "--version") {
            std::cerr << "2026.0.1" << std::endl;
            std::cerr << std::endl;
            return isConfigValid();
        }
        if (i == 1) {
            if (std::filesystem::is_directory(arg)) {
                searchableRootDirectory = arg;
            }
            else {
                errorMessage = "Invalid arguments: Unable to find specified directory";
                return isConfigValid();
            }
            continue;
        }
        if (i == 2) {
            parseRespectively(arg, targetExtensions);
            continue;
        }
        if (arg == "-i" || arg == "--ignore") {
            if (i+1 == argc) {
                errorMessage = "Invalid arguments: Please specify directories to ignore";
                return isConfigValid();
            }
            ignoringNextArg = true;
        }
        else {
            errorMessage = "Invalid arguments: Syntax error";
            return isConfigValid();
        }
    }

    isValid = verifySubdirectoriesExistence(searchableRootDirectory, ignoredSearchDirectories);
    errorMessage = !isValid ? "Invalid arguments: One or more subdirectories in given root does not exist" : "";
    return isConfigValid();
}

ConfigParser::ConfigParser() : isValid(false) {}

std::filesystem::path& ConfigParser::getSearchableRootDirectory() {return searchableRootDirectory;}

std::unordered_set<std::string>& ConfigParser::getTargetExtensions() {return targetExtensions;}

std::unordered_set<std::string>& ConfigParser::getIgnoredSearchDirectories() {return ignoredSearchDirectories;}

bool ConfigParser::isConfigValid() const {return isValid;}

void ConfigParser::printErrorMessage() {
    std::cerr << errorMessage << std::endl;
}