#include "array"
#include "algorithm"

template <typename T, typename Lambda, size_t N>
constexpr array<T, N> sort_compile_time(array<T, N> arr, Lambda lambda){
    sort(arr.begin(), arr.end(), lambda);
}
