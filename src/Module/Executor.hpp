/**
 * @file Executor.hpp
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
#include "../Utility/BFSHelper.hpp"
#include "../Utility/FileManager.hpp"
#include <stdexcept>

namespace Module {

class Executor {
    using string = std::string;

public:
    static void exec_query(
        const std::pair<string, string>& info
    ) {
        using Resource::Algorithm;
        static constexpr size_t DIJ_LIM = 5;

        // Now we don't use Dijkstra
        //
        // if (info.first.size() <= DIJ_LIM) {
        //     Algorithm::get(info.first.length())
        //         ->query(info.first, info.second);
        //     return;
        // }

        Utility::BFSHelper bfs_p(
            *Resource::Graph::get(
                info.first.length()
            )
        );
        bfs_p.query(info);
    }
};

} // namespace Module