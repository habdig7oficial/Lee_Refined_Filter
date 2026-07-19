#pragma once

namespace env {
    #if NDEBUG
        constexpr bool dev_mode = false;
    #else 
        constexpr bool dev_mode = true;
    #endif
}

#include "array"
#include "algorithm"

using namespace std;

template <typename T, typename Lambda, size_t N>
constexpr array<T, N> sort_compile_time(array<T, N> arr, Lambda lambda){
    sort(arr.begin(), arr.end(), lambda);
    return arr;
}
