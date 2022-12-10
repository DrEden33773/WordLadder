/**
 * @file Scanner.hpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-12-09
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include "../Resource/MetaData.hpp"
#include "../Utility/FileManager.hpp"

#include <fstream>
#include <iostream>

namespace Module {

class Scanner {
    using fs_path = std::filesystem::path;

    const fs_path& src_path      = Utility::FileManager::Filename::SourceFile;
    const fs_path& test_src_path = Utility::FileManager::Filename::TestSrcFile;

    fs_path      old_src_path;
    std::fstream src_file;

private:
    bool if_need_to_move_src = true;
    void locate_origin_src() {
        bool if_opt_source_exist = std::filesystem::exists(src_path);
        if (if_opt_source_exist) {
            bool if_opt_source_empty = std::filesystem::is_empty(src_path);
            if (!if_opt_source_empty) {
                // should not ReLocate the src
                if_need_to_move_src = false;
                return;
            }
        }
        while (true) {
            std::cout << "Please input the `Path` of source file " << std::endl;
            std::cout << R"( E.G. => C:/Path/Name.txt | C:\\Path\\Name.txt )" << std::endl;
            std::cout << ">>> ";
            std::cin >> old_src_path;
            if (!std::filesystem::exists(old_src_path)) {
                std::cout << "Input path DO NOT EXIST! Please try again... " << std::endl;
                std::cout << std::endl;
                old_src_path.clear();
            } else {
                std::cout << std::endl;
                break;
            }
        }
    }
    void copy_to_src() {
        if (!if_need_to_move_src) {
            return;
        }
        Utility::FileManager::copy_source_file_from(old_src_path);
        std::cout << "Successfully get source file. It had been moved to: " << std::endl;
        std::cout << "\t" << src_path << std::endl;
        std::cout << std::endl;
    }
    void scan_src() {
        using std::cout;
        using std::endl;

        cout << "Now, scan the source file..." << endl
             << endl;

        src_file.open(src_path, std::fstream::in);
        if (!src_file.is_open()) {
            throw std::runtime_error("Cannot open Source File!");
        }
        parser();
        src_file.close();

        cout << "Done!" << endl
             << endl;
    }

private:
    /**
     * @brief parser => Core
     *
     */
    void parser() {
        using Resource::Category_VexList_Map;
        using Resource::Vexes;
        using std::string;

        string received;

        while (src_file >> received) {
            int length = static_cast<int>(received.length());
            (*Category_VexList_Map)[length].push_back(received);
            Vexes->insert(received);
        }
    }

public:
    static void Scan() {
        Scanner scan_p;
        scan_p.locate_origin_src();
        scan_p.copy_to_src();
        scan_p.scan_src();
    }
};

} // namespace Module