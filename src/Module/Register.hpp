/**
 * @file Register.hpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-12-09
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include "../Resource/Algorithm.hpp"
#include "../Resource/Graph.hpp"
#include "../Resource/MetaData.hpp"
#include "../Utility/FileManager.hpp"

#include <algorithm>
#include <stdexcept>

namespace Module {

/* aliases */
template <class K, class V>
using HashMap = std::unordered_map<K, V>;
template <class K>
using HashSet = std::unordered_set<K>;
using std::string;
using std::vector;

using VL = vector<string>;
using VS = HashSet<string>;

class Register {
    /* last_source */
    static string last_source;
    /* partial_match_map */
    static HashMap<string, VS> partial_match_map;

    static auto register_graph(const string& source) {
        using Resource::Category_VexList_Map;
        int length = static_cast<int>(source.length());

        return Resource::Graph::register_with(
            length,
            Category_VexList_Map->at(length)
        );
    }
    static void adjust_graph(const string& source) {
        using Resource::Category_VexList_Map;
        int    length   = static_cast<int>(source.length());
        auto&& vex_list = Category_VexList_Map->at(length);

        reset_partial_match_map();
        build_partial_match_map(source);

        for (auto&& [mask, vex_set] : partial_match_map) {
            VL vex_list {};
            for (const string& vex : vex_set) {
                vex_list.push_back(vex);
            }
            for (int i = 0; i < vex_list.size(); ++i) {
                for (int j = i + 1; j < vex_list.size(); ++j) {
                    const string& from = vex_list.at(i);
                    const string& to   = vex_list.at(j);
                    Resource::Graph::get(length)->InsertArc(
                        from,
                        to,
                        1
                    );
                }
            }
        }
    }
    static void register_dijkstra(const string& source) {
        int length = static_cast<int>(source.length());
        Resource::Algorithm::register_with(
            length,
            *Resource::Graph::get(length)
        );
    }

    static void build_partial_match_map(const string& source) {
        using Resource::Category_VexList_Map;
        int length = static_cast<int>(source.length());

        for (const string& origin : Category_VexList_Map->at(length)) {
            for (int diff = 0; diff < length; ++diff) {
                string mask   = origin;
                mask.at(diff) = '_';
                if (!partial_match_map.contains(mask)) {
                    partial_match_map[mask] = VS();
                }
                partial_match_map[mask].insert(origin);
            }
        }
    }
    static void reset_partial_match_map() {
        partial_match_map.clear();
    }

    static bool if_partial_eq(
        string     lhs,
        string     rhs,
        const int& diff_idx
    ) {
        if (lhs.length() != rhs.length()) {
            throw std::runtime_error("Input words doesn't have same length!");
        }
        lhs[diff_idx] = '_';
        rhs[diff_idx] = '_';
        return lhs == rhs;
    }
    static constexpr bool if_adj_string(
        const string& lhs,
        const string& rhs
    ) {
        if (lhs.length() != rhs.length()) {
            throw std::runtime_error("Input words doesn't have same length!");
        }
        int diff_time = 0;
        for (int i = 0; i < lhs.length(); ++i) {
            if (lhs.at(i) != rhs.at(i)) {
                ++diff_time;
            }
        }
        return (diff_time == 1) ? true : false;
    }

public:
    static void registry(
        const std::pair<
            string, string>& info
    ) {
        if (last_source.length() == info.first.length()) {
            return; // don't need to registry
        }

        register_graph(info.first);
        adjust_graph(info.first);

        // Now we don't use Dijkstra Algorithm
        //
        // if (last_source != info.first) {
        //     register_dijkstra(info.first);
        // }

        last_source = info.first;
    }
};

string              Register::last_source       = {};
HashMap<string, VS> Register::partial_match_map = {};

} // namespace Module