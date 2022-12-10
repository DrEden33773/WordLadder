/**
 * @file MetaData.hpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-12-09
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <memory>
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

inline namespace MetaData {
    static const Rc<CVsMap> Category_VexSet_Map  = make_shared<CVsMap>(); // no need!
    static const Rc<CVlMap> Category_VexList_Map = make_shared<CVlMap>(); // in need!
    static const Rc<VS>     Vexes                = make_shared<VS>();     // in need!
} // namespace MetaData

} // namespace Resource