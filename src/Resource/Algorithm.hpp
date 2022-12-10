/**
 * @file Algorithm.hpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-12-09
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include "../Utility/Dijkstra.hpp"
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

class Algorithm {
    static HashMap<int, Rc<Utility::Dijkstra<string>>> Dijkstra_Algos;

public:
    /**
     * @brief register_with
     *
     * @param length
     * @param graph
     */
    static void register_with(
        const int&              length,
        Utility::Graph<string>& graph
    ) {
        if (Dijkstra_Algos[length]) {
            return;
        }
        auto&& registered_dijkstra = make_shared<Utility::Dijkstra<string>>(
            graph
        );
        Dijkstra_Algos[length] = registered_dijkstra;
    }

    /**
     * @brief get
     *
     * @param length
     * @return auto
     */
    static auto get(const int& length) {
        if (!Dijkstra_Algos[length]) {
            throw std::runtime_error("Dijkstra Algorithm hasn't been registered yet!");
        }
        return Dijkstra_Algos[length];
    }

    /**
     * @brief set
     *
     * @param length
     * @param graph
     */
    static void set(
        const int&              length,
        Utility::Graph<string>& graph
    ) {
        Dijkstra_Algos[length].reset();
        auto&& registered_dijkstra = make_shared<Utility::Dijkstra<string>>(
            graph
        );
        Dijkstra_Algos[length] = registered_dijkstra;
    }
};

HashMap<int, Rc<Utility::Dijkstra<string>>> Algorithm::Dijkstra_Algos
    = HashMap<int, Rc<Utility::Dijkstra<string>>>();

} // namespace Resource