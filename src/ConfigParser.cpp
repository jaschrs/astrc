//
// Created by Jasper on 2026-05-19.
//

#include "../include/ConfigParser.hpp"
#include "../include/third_party/json.hpp"
#include <string>
#include <iostream>
#include <fstream>

ConfigStatus ConfigParser::parseArgs(char* argv[]) {

    std::string arg = argv[1];

    // very ugly parsing
    if (arg == "-h" || arg == "--help") {
        std::cerr << "Usage: StaticTrace <DIRECTORY>\n\n";
        std::cerr << "Configurations:\n\n";
        std::cerr << "\t-h, --help\tPrint this help message\n\n";
        std::cerr << "\t-v, --version\tPrint version number \n\n";
        std::cerr << "\tExample: \tStaticTrace ./MyProject \n\n";
        return configStatus;
    }
    if (arg == "-v" || arg == "--version") {
        std::cerr << "2026.0.1\n\n";
        return configStatus;
    }
    if (std::filesystem::is_directory(arg) && std::filesystem::exists(arg + "/statictraceconfig.json")) {
        searchableRootDirectory = arg;
        std::cout << "Found config file, attempting to parse...\n";
        std::ifstream config(searchableRootDirectory.generic_string() + "/statictraceconfig.json");
        parseConfigFile(config);
    }
    else {
        errorMessage = "Invalid arguments: Unable to find specified directory or config file";
        return configStatus;
    }

    configStatus = !verifySubdirectoriesExistence(searchableRootDirectory, ignoredSearchDirectories) ? ConfigStatus::FAILURE : configStatus;
    errorMessage = configStatus == ConfigStatus::FAILURE ? "Invalid config: One or more subdirectories in given root does not exist" : "";

    return configStatus;
}

void ConfigParser::parseConfigFile(std::ifstream &configFile) {
    nlohmann::json config;
    try {
        config = nlohmann::json::parse(configFile);
    }
    catch (std::exception& e) {
        std::cerr << e.what() << "\n";
        configStatus = ConfigStatus::FAILURE;
        return;
    }

    if (!(config.contains("targetExtensions") && config["targetExtensions"].is_array())) {
        errorMessage = "Missing 'targetExtensions' array";
        configStatus = ConfigStatus::FAILURE;
        return;
    }

    if (!(config.contains("scanExtensions") || config["scanExtensions"].is_array())) {
        configStatus = ConfigStatus::MISSING_SCAN_EXTENSIONS;
    }

    if (!(config.contains("ignoreDirectories") || config["ignoreDirectories"].is_array())) {
        if (configStatus == ConfigStatus::MISSING_SCAN_EXTENSIONS) configStatus = ConfigStatus::MISSING_BOTH;
        else configStatus = ConfigStatus::MISSING_IGNORE_DIRECTORIES;
    }

    try {
        for (const auto& entry : config["targetExtensions"]) {
            targetExtensions.insert(entry.get<std::string>());
        }

        if (configStatus == ConfigStatus::SUCCESS || configStatus == ConfigStatus::MISSING_IGNORE_DIRECTORIES) {
            for (const auto& entry : config["scanExtensions"]) {
                scannableExtensions.insert(entry.get<std::string>());
            }
        }

        if (configStatus == ConfigStatus::SUCCESS || configStatus == ConfigStatus::MISSING_SCAN_EXTENSIONS) {
            for (const auto& entry : config["ignoreDirectories"]) {
                ignoredSearchDirectories.insert(entry.get<std::string>());
            }
        }
    }
    catch (std::exception& e) {
        configStatus = ConfigStatus::FAILURE;
        errorMessage = "Error parsing config file";
        return;
    }

    if (configStatus == ConfigStatus::FAILURE) configStatus = ConfigStatus::SUCCESS;
}

bool ConfigParser::verifySubdirectoriesExistence(std::filesystem::path &directory, std::unordered_set<std::string> &set) {
    for (const auto &subdirectory : set) {
        if (!std::filesystem::is_directory(directory.generic_string() + "/" + subdirectory)) {
            return false;
        }
    }
    return true;
}

ConfigParser::ConfigParser() : configStatus(ConfigStatus::FAILURE) {}

std::filesystem::path& ConfigParser::getSearchableRootDirectory() {return searchableRootDirectory;}

std::unordered_set<std::string>& ConfigParser::getTargetExtensions() {return targetExtensions;}

std::unordered_set<std::string>& ConfigParser::getIgnoredSearchDirectories() {return ignoredSearchDirectories;}

std::unordered_set<std::string>& ConfigParser::getScannableExtensions() {return scannableExtensions;}

std::string ConfigParser::getErrorMessage() {return errorMessage;}