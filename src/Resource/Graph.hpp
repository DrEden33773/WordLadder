/**
 * @file Graph.hpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-12-09
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include "../Utility/Graph.hpp"

#include <memory>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace Resource {

using std::make_shared;
using std::shared_ptr;
using std::string;
using std::unordered_map;
using std::unordered_set;
using std::vector;

template <class K, class V>
using HashMap = std::unordered_map<K, V>;
template <class K>
using HashSet = std::unordered_set<K>;
template <class T>
using Rc = shared_ptr<T>; // Reference-Counting Auto Pointer

using VexList = vector<string>;
using VL      = VexList;
using VexSet  = HashSet<string>;
using VS      = VexSet;
using CVlMap  = HashMap<int, VL>;
using CVsMap  = HashMap<int, VS>;

class Graph {
    static HashMap<int, Rc<Utility::Graph<string>>> Graphs;

public:
    /**
     * @brief register_with
     *
     * @param vexes
     */
    static auto register_with(const int& length, const VexList& vexes) {
        if (Graphs[length]) {
            return false;
        }
        auto&& registered_graph = make_shared<Utility::Graph<string>>(
            vexes,
            true,
            false
        );
        Graphs[length] = registered_graph;
        return true;
    }

    /**
     * @brief set
     *
     * @param vexes
     */
    static void set(const int& length, const VexList& vexes) {
        Graphs[length].reset();
        auto&& new_graph = make_shared<Utility::Graph<string>>(
            vexes,
            true,
            false
        );
        Graphs[length] = new_graph;
    }

    /**
     * @brief get
     *
     * @param length
     * @return Rc<Utility::Graph<string>>
     */
    static Rc<Utility::Graph<string>> get(const int& length) {
        if (!Graphs[length]) {
            throw std::runtime_error("Unregistered Graph!");
        }
        return Graphs[length];
    }
};

HashMap<int, Rc<Utility::Graph<string>>> Graph::Graphs
    = HashMap<int, Rc<Utility::Graph<string>>>();

} // namespace Resource