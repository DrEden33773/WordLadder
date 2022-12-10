/**
 * @file BasicWordLadder.hpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-12-07
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <algorithm>
#include <exception>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <queue>
#include <stdexcept>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

class BasicWordLadder {
    template <class T>
    using vector = std::vector<T>;
    template <class T>
    using queue = std::queue<T>;
    template <class T>
    using hash_set = std::unordered_set<T>;
    template <class T>
    using unordered_set = std::unordered_set<T>;
    template <class T>
    using shared_ptr = std::shared_ptr<T>;
    template <class T>
    using unique_ptr = std::unique_ptr<T>;
    using string     = std::string;

private:
    /* source and target */
    string source;
    string target;
    size_t length = 0;

    /* idx of difference */
    vector<size_t> idx_of_difference;

    /* RouteInfo */
    struct TransferInfo {
        string           word;
        vector<string>   route;
        hash_set<size_t> transferred;
    };

    /* all route */
    vector<vector<string>> all_route;
    size_t                 num_of_route = 0;

    /* transfer tool */
    string transfer(const string& input, const size_t& idx) {
        string ret = input;
        if (idx >= input.length()) {
            throw std::out_of_range("Input index is out_of_range");
        }
        ret[idx] = target[idx];
        return ret;
    }
    void emplace_transfer(string& out, const size_t& idx) {
        if (idx >= out.length()) {
            throw std::out_of_range("Input index is out_of_range");
        }
        out[idx] = target[idx];
    }

private:
    void input() {
        using std::cin;
        using std::cout;
        using std::endl;

        cout << "Please input two word (length should be equal)" << endl;
        cout << ">>> ";
        cin >> source >> target;
        if (source.length() != target.length()) {
            throw std::runtime_error("source.length() != target.length()");
        }
        length = source.length();
        cout << endl;
    }
    void cmp_two_words() {
        for (size_t idx = 0; idx < length; ++idx) {
            if (source[idx] != target[idx]) {
                idx_of_difference.push_back(idx);
            }
        }
    }
    void BFS(bool if_basic = false) {
        using std::make_shared;
        using std::make_unique;

        auto         heap_queue = make_unique<queue<TransferInfo>>();
        TransferInfo first      = { source, { source } };
        heap_queue->push(first);

        while (!heap_queue->empty()) {
            for (size_t curr_level = heap_queue->size(); curr_level > 0;
                 --curr_level) {
                // get curr
                auto&& curr = heap_queue->front();
                // process
                if (curr.word == target) {
                    if (!if_basic) {
                        all_route.push_back(curr.route);
                    }
                    ++num_of_route;
                } else {
                    for (auto idx : idx_of_difference) {
                        if (!curr.transferred.contains(idx)) {
                            // update to_push
                            auto to_push = curr;
                            emplace_transfer(to_push.word, idx);
                            to_push.transferred.insert(idx);
                            to_push.route.push_back(to_push.word);
                            // push into queue
                            heap_queue->push(to_push);
                        }
                    }
                }
                // pop curr
                heap_queue->pop();
            }
        }
    }
    void output() {
        using std::cin;
        using std::cout;
        using std::endl;

        cout << "Here're the results :" << endl
             << endl;

        for (auto&& route : all_route) {
            for (auto&& word : route) {
                cout << word << " ";
            }
            cout << endl;
        }
        cout << endl;

        cout << "There're { " << num_of_route << " } different transfers" << endl
             << endl;
    }
    void write_to_file() {
        using std::cin;
        using std::cout;
        using std::endl;
        using std::fstream;

        using path  = std::filesystem::path;
        path Root   = "File";
        path Result = Root / "result.txt";

        fstream file(Result, fstream::out | fstream::trunc);
        if (!file.is_open()) {
            throw std::runtime_error("Cannot create `result.txt`");
        }

        try {
            file << "Here're the results :" << endl
                 << endl;
            for (auto&& route : all_route) {
                for (auto&& word : route) {
                    file << word << " ";
                }
                file << endl;
            }
            file << endl;
            file << "There're { " << num_of_route << " } different transfers" << endl
                 << endl;
        } catch (const std::exception& e) {
            cout << e.what() << endl
                 << endl;
        }
        file.close();

        cout << "Successfully write into file!" << endl
             << endl;
        cout << "There're { " << num_of_route << " } different transfers" << endl
             << endl;
    }
    void basic_output() {
        using std::cin;
        using std::cout;
        using std::endl;

        cout << "Succeeded!" << endl
             << endl;

        cout << "There're { " << num_of_route << " } different transfers" << endl
             << endl;
    }

public:
    static void NonFileExec() {
        BasicWordLadder solution;
        solution.input();
        solution.cmp_two_words();
        solution.BFS(false);
        solution.output();
    }
    static void WithFileExec() {
        BasicWordLadder solution;
        solution.input();
        solution.cmp_two_words();
        solution.BFS(false);
        solution.write_to_file();
    }
    static void NonFileBasicExec() {
        BasicWordLadder solution;
        solution.input();
        solution.cmp_two_words();
        solution.BFS(true);
        solution.basic_output();
    }
};