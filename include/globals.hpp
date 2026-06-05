//
// Created by Jasper on 2026-06-05.
//

#ifndef STATICTRACE_GLOBALS_H
#define STATICTRACE_GLOBALS_H

enum ConfigStatus : uint8_t {
    SUCCESS = 0, // found all arguments
    MISSING_SCAN_EXTENSIONS = 1, // only "scanExtensions" key is missing
    MISSING_IGNORE_DIRECTORIES = 2, // only "ignoreDirectories" key is missing
    MISSING_BOTH = 3, // both "scanExtensions" key and "ignoreDirectories" key is missing
    FAILURE = 4 // other failure
};

inline ConfigStatus status = FAILURE;

#endif //STATICTRACE_GLOBALS_H
