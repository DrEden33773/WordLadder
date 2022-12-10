/**
 * @file ConceptLib.hpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-11-19
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <concepts>
#include <fstream>
#include <functional>
#include <istream>
#include <ostream>

namespace Utility {

template <class T>
concept StdOut = requires(T a, std::ostream& b) {
    { b << a };
};

template <class T>
concept StdIn = requires(T a, std::ostream& b) {
    { b >> a };
};

template <class T>
concept StdIO = StdOut<T> and StdIn<T>;

template <class T>
concept FsOut = requires(T a, std::fstream& b) {
    { b << a };
};

template <class T>
concept FsIn = requires(T a, std::fstream& b) {
    { b >> a };
};

template <class T>
concept FsIO = FsOut<T> and FsIn<T>;

template <typename T>
concept Hash = requires(T a) {
    { std::hash<T> {}(a) } -> std::convertible_to<std::size_t>;
};

} // namespace Utility