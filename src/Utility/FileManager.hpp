/**
 * @file FileManager.hpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-12-09
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <algorithm>
#include <filesystem>
#include <iostream>
#include <stdexcept>
#include <vector>

namespace Utility::FileManager {

namespace fs = std::filesystem;

namespace Path {
    /* root */
    static const fs::path Root     = "Files";
    static const fs::path TestRoot = "TestFiles";
} // namespace Path

namespace Filename {
    /* Use this to build the `Route` */
    static const fs::path SourceFile = Path::Root / "source.txt";
    /* test_src.txt */
    static const fs::path TestSrcFile = Path::TestRoot / "test_source.txt";
} // namespace Filename

/* all_path in a vec */
static const std::vector<fs::path> all_path {
    Path::Root,
    Path::TestRoot,
};

static void build_all_path() {
    std::for_each(
        all_path.begin(),
        all_path.end(),
        [](const fs::path& curr) {
            if (!fs::exists(curr)) {
                try {
                    fs::create_directories(curr);
                } catch (fs::filesystem_error& e) {
                    std::cout << "Could not create directory, because: " << e.what() << std::endl;
                }
            }
        }
    );
}
static void check_all_path_existence() {
    std::for_each(
        all_path.begin(),
        all_path.end(),
        [](const fs::path& curr) {
            if (!fs::exists(curr)) {
                throw std::runtime_error("A FilePath is NOT exist!");
            }
        }
    );
}
static void path_init() {
    build_all_path();
    check_all_path_existence();
    std::cout << "Path_Init Succeeded!" << std::endl;
    std::cout << std::endl;
}
static void copy_source_file_from(const fs::path& from) {
    try {
        fs::copy_file(from, Filename::SourceFile);
    } catch (fs::filesystem_error& e) {
        std::cout << "Could not copy, because: " << e.what() << std::endl;
    }
}

} // namespace Utility::FileManager