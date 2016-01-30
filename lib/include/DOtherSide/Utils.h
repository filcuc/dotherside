#pragma once

// std
#include <algorithm>
#include <functional>
#include <type_traits>
// Qt
#include <QtGlobal>

namespace DOS
{

template <typename T>
struct wrapped_array {
    wrapped_array(T* first, T* last) : begin_ {first}, end_ {last} {}
    wrapped_array(T* first, std::ptrdiff_t size)
        : wrapped_array {first, first + size} {}

    T*  begin() const Q_DECL_NOEXCEPT { return begin_; }
    T*  end() const Q_DECL_NOEXCEPT { return end_; }

    T* begin_;
    T* end_;
};

template <typename T>
wrapped_array<T> wrap_array(T* first, std::ptrdiff_t size) Q_DECL_NOEXCEPT
{ return {first, size}; }

template <typename T, typename G>
std::vector<T> toVector(G* first, std::ptrdiff_t size) Q_DECL_NOEXCEPT
{
    const wrapped_array<G> array = wrap_array(first, size);
    std::vector<T> result;
    for (auto it = array.begin(); it != array.end(); ++it)
        result.emplace_back(T(*it));
    return result;
}

template <typename T, typename K, typename R = typename std::result_of<K(T)>::type>
std::vector<R> toVector(T* first, std::ptrdiff_t size, K f) Q_DECL_NOEXCEPT
{
    wrapped_array<T> array = wrap_array<T>(first, size);
    std::vector<R> result;
    for (auto it = array.begin(); it != array.end(); ++it)
        result.emplace_back(R(f(*it)));
    return result;
}

}
