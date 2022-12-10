/**
 * @file Query.hpp
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

#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>

namespace Module {

class Query {
    using string = std::string;
    string source;
    string target;

    void input() {
        using Resource::Vexes;
        using std::cin;
        using std::cout;
        using std::endl;

        while (true) {
            source.clear();
            target.clear();
            cout << "Please input two word (length should be equal)" << endl;
            cout << "(You could input `-1` only to exit)" << endl;
            cout << ">>> ";
            cin >> source;
            if (source == "-1") {
                exit(0);
            }
            cin >> target;
            if (Vexes->contains(source) && Vexes->contains(target)) {
                if (source.length() == target.length()) {
                    break;
                } else {
                    cout << "You can only query words with same length, try again..." << endl;
                    cout << endl;
                }
            } else {
                cout << "There must be at least one word not exist, try again..." << endl;
                cout << endl;
            }
        }
        cout << endl;
    }
    std::pair<string, string> return_info() {
        return std::make_pair(source, target);
    }

public:
    static auto query() {
        Query query_p;
        query_p.input();
        return query_p.return_info();
    }
};

} // namespace Module