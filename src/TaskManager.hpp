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
    while (true) {
        auto info = Module::Query::query();
        Module::Register::registry(info); // fixed the problem, register could be fast
        Module::Executor::exec_query(info);
    }
}

} // namespace Task