/**
 * @file BFSHelper.hpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-12-10
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include "Graph.hpp"

#include <algorithm>
#include <iostream>
#include <iterator>
#include <list>
#include <stdexcept>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

namespace Utility {

using std::list;
using std::pair;
using std::queue;
using std::string;
using std::unordered_set;
using std::vector;

class BFSHelper {
    Graph<string>* Data = nullptr;
    string         from {};
    string         to {};
    list<string>   shortest_route {};

    enum class color : unsigned short {
        white = 0, // unvisited
        grey  = 1, // partially_visited
        black = 2, // totally_visited
    };

    struct VexInfo {
        string       vex;
        list<string> route_to_vex;
    };

    [[nodiscard]] vector<string> get_all_adj_vex(const string& vex) const {
        vector<string> ret;
        vector<int>    all_adj_idx = Data->FindAllAdjIndex(vex);
        ret.reserve(all_adj_idx.size());
        for (const int& idx : all_adj_idx) {
            ret.emplace_back(
                Data->Index_V_Map[idx]
            );
        }
        return ret;
    }

    void BFS() {
        unordered_set<string> visited;
        queue<VexInfo>        queue;

        VexInfo src_info {
            .vex          = from,
            .route_to_vex = { from }
        };
        queue.push(std::move(src_info));
        visited.insert(from);

        while (!queue.empty()) {
            size_t curr_level_size = queue.size();
            while (curr_level_size > 0) {
                VexInfo&       curr_info   = queue.front();
                vector<string> all_adj_vex = get_all_adj_vex(curr_info.vex);
                for (auto&& adj_vex : all_adj_vex) {
                    if (adj_vex == to) {
                        VexInfo final_info = curr_info;
                        final_info.vex     = to;
                        final_info.route_to_vex.push_back(to);
                        shortest_route = final_info.route_to_vex;
                        return;
                    }
                    if (!visited.contains(adj_vex)) {
                        VexInfo adj_info = curr_info;
                        adj_info.vex     = adj_vex;
                        adj_info.route_to_vex.push_back(adj_vex);
                        queue.push(adj_info);
                        visited.insert(adj_vex);
                    }
                }
                queue.pop();
                --curr_level_size;
            }
        }
    }

    void show_result() const {
        using std::cout;
        using std::endl;
        static constexpr int DIV = 5;

        if (shortest_route.empty()) {
            cout << "Route is not exist!" << endl;
            cout << endl;
            return;
        }

        cout << "The shortest route is => " << endl;
        int idx = 0;
        for (auto&& vex : shortest_route) {
            if (idx % DIV == 0) {
                cout << endl;
                cout << "\t";
            }
            cout << vex << " ";
            ++idx;
        }
        cout << endl;
        cout << endl;

        cout << "The minimum distance is => ";
        cout << shortest_route.size() - 1 << endl;
        cout << endl;
    }

public:
    explicit BFSHelper(Utility::Graph<string>& graph)
        : Data(&graph) { }

    void query(const pair<string, string>& info) {
        from = info.first;
        to   = info.second;
        BFS();
        show_result();
    }
};

} // namespace Utility