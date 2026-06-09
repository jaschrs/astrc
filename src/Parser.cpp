//
// Created by Jasper on 2026-05-19.
//

#include "../include/Parser.hpp"
#include "../include/third_party/json.hpp"
#include <string>
#include <iostream>
#include <fstream>

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

ConfigStatus status = FAILURE;

ConfigStatus Parser::parseArgs(int argc, char* argv[]) {

    if (argc == 1) {
        errorMessage = "Missing arguments";
        return status;
    }
    std::string arg = argv[1];

    // very ugly parsing
    if (arg == "-h" || arg == "--help") {
        std::cerr << "Usage: StaticTrace <DIRECTORY>\n\n";
        std::cerr << "Configurations:\n\n";
        std::cerr << "\t-h, --help\tPrint this help message\n\n";
        std::cerr << "\t-v, --version\tPrint version number \n\n";
        std::cerr << "\tExample: \tStaticTrace ./MyProject \n\n";
        return status;
    }
    if (arg == "-v" || arg == "--version") {
        std::cerr << "2026.0.1\n\n";
        return status;
    }
    if (std::filesystem::is_directory(arg) && std::filesystem::exists(arg + "/statictraceconfig.json")) {
        searchableRootDirectory = arg;
        std::cout << "Found config file, attempting to parse...\n";
        std::ifstream config(searchableRootDirectory / "statictraceconfig.json");
        parseConfigFile(config);
        if (status == FAILURE) return status;
    }
    else {
        errorMessage = "Invalid arguments: Unable to find specified directory or config file";
        return status;
    }

    return status;
}

void Parser::parseConfigFile(std::ifstream &configFile) {
    nlohmann::json config;
    try {
        config = nlohmann::json::parse(configFile);
    }
    catch (std::exception& e) {
        std::cerr << e.what() << "\n";
        status = FAILURE;
        return;
    }

    const bool hasTargetExtensions = config.contains("targetExtensions") && config["targetExtensions"].is_array();
    const bool hasScanExtensions = config.contains("scanExtensions") && config["scanExtensions"].is_array();
    const bool hasIgnoreDirectories = config.contains("ignoreDirectories") && config["ignoreDirectories"].is_array();

    if (!hasTargetExtensions) {
        errorMessage = "Missing 'targetExtensions' array";
        status = FAILURE;
        return;
    }

    if (!hasScanExtensions && !hasIgnoreDirectories) {
        status = MISSING_BOTH;
        std::cout << "Missing both 'scanExtensions' & 'ignoreDirectories' array.. continuing\n";
        goto parse;
    }

    if (!hasScanExtensions) {
        status = MISSING_SCAN_EXTENSIONS;
        scannableExtensions = std::move(defaultScannableExtensions);
        std::cout << "Missing 'scanExtensions' array.. will use default\n";
    }

    if (!hasIgnoreDirectories) {
        status = MISSING_IGNORE_DIRECTORIES;
        std::cout << "Missing 'ignoreDirectories' array.. continuing\n";
    }

parse:
    try {
        for (const auto& entry : config["targetExtensions"]) {
            targetExtensions.insert(entry.get<std::string>());
        }
        std::cout << "Parsed targetExtensions..\n";

        if (hasIgnoreDirectories) {
            for (const auto& entry : config["ignoreDirectories"]) {
                ignoredSearchDirectories.insert(entry.get<std::string>());
            }
            std::cout << "Parsed ignoreDirectories..\n";
        }

        if (hasScanExtensions) {
            for (const auto& entry : config["scanExtensions"]) {
                scannableExtensions.insert(entry.get<std::string>());
            }
            std::cout << "Parsed scanExtensions..\n";
        }
    }
    catch (std::exception& e) {
        status = FAILURE;
        errorMessage = "Error parsing config file";
        return;
    }

    if (status == FAILURE) status = SUCCESS;
}

Parser::Parser() = default;

const std::filesystem::path& Parser::getSearchableRootDirectory() const {return searchableRootDirectory;}

const std::unordered_set<std::string>& Parser::getTargetExtensions() const {return targetExtensions;}

const std::unordered_set<std::string>& Parser::getIgnoredSearchDirectories() const {return ignoredSearchDirectories;}

const std::unordered_set<std::string>& Parser::getScannableExtensions() const {return scannableExtensions;}

const std::string Parser::getErrorMessage() const {return errorMessage;}