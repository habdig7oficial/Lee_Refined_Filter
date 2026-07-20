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

template<typename T, size_t N>
constexpr T sum(array<T, N> arr){
    static_assert(is_arithmetic_v<T>, "Type must be a number");

    T total = 0;

    for(int i = 0; i < N; i++)
        total += arr[i];
    
    return total;
}

template<typename T, size_t N>
constexpr array<T, N> normalize(array<T, N> arr){
    static_assert(is_arithmetic_v<T>, "Type must be a number");

    array<T, N> new_arr;
    T sum_arr = sum<T, N>(arr);

    for(int i = 0; i < N; i++)
        new_arr[i] = arr[i] / sum_arr;
    
    return new_arr;
}