#pragma once

namespace env {
    #if NDEBUG
        constexpr bool dev_mode = false;
    #else 
        constexpr bool dev_mode = true;
    #endif
}

#include "array"
#include "tuple"
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

template<typename T, size_t N>
constexpr tuple<uint, T> min(array<T, N> arr){
    static_assert(is_arithmetic_v<T>, "Type must be a number");

    T total = arr[0];
    uint pos = 0;

    for(int i = 1; i < N; i++)
        if(arr[i] < total){
            total = arr[i];
            pos = i;
        }
            
    return {pos, total};
}

template<typename T>
constexpr T const_abs(T var){
    return (var < 0)? -var : var;
}

template<typename T, size_t N>
constexpr array<T, N> abs(array<T, N> arr){
    static_assert(is_arithmetic_v<T>, "Type must be a number");

    array<T, N> new_arr;

    for(int i = 0; i < N; i++)
        new_arr[i] = const_abs(arr[i]);
    
    return new_arr;
}

template<typename T, size_t N, size_t M>
constexpr array<T, N> diff(array<T, N> a, array<T, M> b){
    array<T, N>res;


    //auto it = set_difference(at.begin(), at.end(), bt.begin(), bt.end(), res.begin());

    return a;
}