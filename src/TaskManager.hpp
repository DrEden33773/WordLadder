/**
 * @file TaskManager.hpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-12-09
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include "Module/Executor.hpp"
#include "Module/Query.hpp"
#include "Module/Register.hpp"
#include "Module/Scanner.hpp"
#include "Utility/FileManager.hpp"

namespace Task {

void run_all_tasks() {
    Utility::FileManager::path_init();
    Module::Scanner::Scan();

    // The `loop` query could cost too much memory,
    // we need to add an algorithm to reduce memory usage.
    //
    // The easiest way is to let `GraphPool` automatically unregister
    // the earliest constructed graph while memory usage reaches to a limit
    // (That limit should depend on the size of the host's memory size)
    //
    // while (true) {
    //     auto info = Module::Query::query();
    //     Module::Register::registry(info);
    //     Module::Executor::exec_query(info);
    // }

    auto info = Module::Query::query();
    Module::Register::registry(info);
    Module::Executor::exec_query(info);
}

} // namespace Task