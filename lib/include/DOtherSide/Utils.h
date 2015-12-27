#pragma once

#include <algorithm>

namespace DOS
{

template <typename T>
struct wrapped_array {
    wrapped_array(T* first, T* last) : begin_ {first}, end_ {last} {}
    wrapped_array(T* first, std::ptrdiff_t size)
        : wrapped_array {first, first + size} {}

    T*  begin() const noexcept { return begin_; }
    T*  end() const noexcept { return end_; }

    T* begin_;
    T* end_;
};

template <typename T>
wrapped_array<T> wrap_array(T* first, std::ptrdiff_t size) noexcept
{ return {first, size}; }

template <typename T, typename G>
std::vector<T> toVector(const wrapped_array<G>& array)
{
    std::vector<T> result;
    std::copy(array.begin(), array.end(), result.begin());
    return result;
}
}
