# astrc

[![Build Status](https://github.com/jaschrs/astrc/actions/workflows/ci.yml/badge.svg)](https://github.com/jaschrs/astrc/actions)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![C++20](https://img.shields.io/badge/C++-20-blue.svg)](https://isocpp.org/)

astrc (asset trace) is a highly optimized command-line tool to find unreferenced assets (or any file really) in a large codebase, helping remove dead files and optimize your projects!

## How it Works

1. Parses given config file to identify file mappable file extensions (the files that will be searched for in source files) e.g. static images in a web project. Optionally identifies specified source file extensions to search in (e.g. search for .png in .jsx files). Optionally ignores specified folders to optimize search (e.g. ignore /build, /node_modules).
2. Recursively explores given root directory & creates a map of all given file extensions.
3. Recursively explores root directory again, instead reading source files for mapped assets.
4. If any mapped assets are found unreferenced, those are the files holding zero value in your project. 

## Optimizations

* Memory-mapped IO: Instead of reading line by line straight from disk.
* Aho-Corasick Searching: Find mapped assets in a single pass.
* Simple Config: Managed via a simple `.astrc` or `.astrc.json` file for CI.

## Usage

```bash
git clone https://github.com/jaschrs/astrc.git
cd astrc
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
cd build
```

Navigate to project directory and create a .astrc or .astrc.json file to config the tool (yes, comments are allowed). Below is an example.

In this case, the tool will look for .png files in .jsx files, and retrieve any unreferenced mapped files. Technically one can search for any file extension and/or scan in any type of source file.

Technically version isn't required, but a recommended convention (to check version `astrc -v`, `astrc --version`.

```json
{
  "version": "2026.0.1",
  "targetExtensions": [ // Look for these files in source files
    ".png",
    ".jpg",
    ".jpeg",
    ".gif",
    ".svg"
  ],
    "scanExtensions": [ // Check these files for assets specified above
    ".html",
    ".txt",
    ".jsx",
    ".ts",
    ".tsx",
    ".vue",
    ".cpp",
    ".hpp",
    ".py"
  ],
  "ignoreDirectories": [ // directories to skip searching
    "node_modules",
    "build"
  ]
}
```

Any compatible with std::filesystem:
```bash
astrc <your_project_directory>
```
