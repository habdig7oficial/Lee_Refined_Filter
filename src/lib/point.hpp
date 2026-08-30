#pragma once

inline constexpr size_t dimension =  9;
inline constexpr size_t dimension_inner = 3;

inline constexpr size_t inner_half = dimension_inner / 2;
inline constexpr size_t inner_area = (dimension_inner * dimension_inner);

inline constexpr size_t size_point = (dimension / 2 <= (SCHAR_MAX >> (CHAR_BIT / 2)))? CHAR_BIT / 2 : CHAR_BIT;
inline constexpr size_t thickness = 3;
//#define RELEVANT_POINTS_SIZE(N) (2 * INNER_AREA * (N + 1)) 

#define EPSILON 1e-9

#define SIDE_A true
#define SIDE_B false

#define NOT_ROTATED true
#define ROTATED false

/* In side A NOT_ROTATED is (x, y) */
namespace Magic {
    struct Point {
        signed char first : size_point;
        signed char second : size_point;

        auto operator <=> (const Point&) const = default;


    friend ostream& operator << (ostream& os, const Point& point){
        os << "Point {" << (int)point.first << ", " << (int)point.second << "} ";
        return os;
    }
    };
}

using namespace Magic;

auto sorting_lambda = [](const Point& a, const Point &b){
    if(a.second == b.second){
        return a.first < b.first;
    }
    else
        return a.second > b.second;
};

template<typename T> 
constexpr vector<T> filter(vector<T> arr, uint threshold){
    vector<T> new_vec;

    for(const Point& point : arr){
        uint c = count(arr.begin(), arr.end(), point);

        if(c < threshold)
            continue;
        
        new_vec.push_back(point);
    }

    sort(new_vec.begin(), new_vec.end());
    
    auto cleaned = unique(new_vec.begin(), new_vec.end());
    new_vec.erase(cleaned, new_vec.end());

    return new_vec;
}

constexpr vector<Point> mark_relevant(const span<const Point>arr){
    vector<Point> relevant_points;

    for(auto [rx, ry] : arr ){
        for(signed char j = ry - inner_half; j <= ry + inner_half; j++){
            for(signed char i = rx - inner_half; i <= rx + inner_half; i++){

                /* Cap out of bounds points */
                if(const_abs(i) > (dimension / 2) - 1 || const_abs(j) > (dimension / 2) - 1)
                    continue;

                /* Ensure that the mirror points are placed */
                if(rx == 0){
                    for(int k = 0; k < dimension; k++)
                        relevant_points.push_back(Point{i, j});

                    continue;   
                }       
                
                    
        
                relevant_points.push_back(Point{i, j});
            }
        }
    }

    return relevant_points;
}

template<size_t N> 
constexpr size_t filtered_size(const array<Point, N>arr, uint threshold){ return filter(mark_relevant(arr), threshold).size(); }


template<size_t N, size_t M>
constexpr array<Point, M> gen_static(const array<Point, N>& arr, uint threshold){
    vector<Point> marked = mark_relevant(arr);
    vector<Point> filter_arr = filter(marked, threshold);

    array<Point, M> final_arr;

    copy(filter_arr.begin(), filter_arr.end(), final_arr.begin());

    return final_arr;
}

template<size_t N, size_t M>
constexpr array<Point, N> diff(array<Point, N> a, array<Point, M> b){
    array<Point, N> arr{};

    set_difference(a.begin(), a.end(), b.begin(), b.end(), arr.begin());

    return arr;
}

constexpr array w0_arr = {
        Magic::Point{0, 1}, 
        Magic::Point{1, 1}, Magic::Point{1, 0}, Magic::Point{1, -1},
        Magic::Point{2, 1}, Magic::Point{2, 0}, Magic::Point{2, -1},
        Magic::Point{3, 1}, Magic::Point{3, 0}, Magic::Point{3, -1},
        Magic::Point{4, 1}, Magic::Point{4, 0}, Magic::Point{4, -1},
        Magic::Point{5, 1}, Magic::Point{5, 0}, Magic::Point{5, -1}
};
//constinit auto window0 = magic_points_factory<w0_arr, dimension_inner, 0>();

constexpr array w1_arr = {
        Magic::Point{1, -1}, Magic::Point{0, 1},
        Magic::Point{1, 1}, Magic::Point{1, 0},
        Magic::Point{2, 2}, Magic::Point{2, 1}, Magic::Point{2, 0},
        Magic::Point{3, 2}, Magic::Point{3, 1}, Magic::Point{3, 0},
        Magic::Point{4, 2}, Magic::Point{4, 1}, Magic::Point{4, 0},
        Magic::Point{5, 2}, Magic::Point{5, 1}, Magic::Point{5, 0}, 
};
//constinit auto window1 = magic_points_factory<w1_arr, dimension_inner, 1>();

constexpr array w2_arr = {
        Magic::Point{0, 1},
        Magic::Point{1, 1}, Magic::Point{1, 0}, Magic::Point{1, -1},
        Magic::Point{2, 2}, Magic::Point{2, 1}, Magic::Point{2, 0},
        Magic::Point{3, 2}, Magic::Point{3, 1},
        Magic::Point{4, 3}, Magic::Point{4, 2}, Magic::Point{4, 1},
        Magic::Point{5, 3}, Magic::Point{5, 2}, Magic::Point{5, 1}
    };
//constinit auto window2 = magic_points_factory<w2_arr, dimension_inner, 2>();

constexpr array w3_arr = {
        Magic::Point{0, 1}, Magic::Point{-1, 1}, 
        Magic::Point{1, 1}, Magic::Point{1, 0},
        Magic::Point{2, 2}, Magic::Point{2, 1}, Magic::Point{2, 0},
        Magic::Point{3, 2}, Magic::Point{3, 1},
        Magic::Point{4, 3}, Magic::Point{4, 2}, Magic::Point{4, 1},
        Magic::Point{5, 4}, Magic::Point{5, 3}, Magic::Point{5, 2}
};
//constinit auto window3 = magic_points_factory<w3_arr, dimension_inner, 3>();

constexpr array w4_arr = {
        Magic::Point{0, 1}, 
        Magic::Point{1, 1}, Magic::Point{1, 0}, Magic::Point{1, -1},
        Magic::Point{2, 2}, Magic::Point{2, 1}, Magic::Point{2, 0},
        Magic::Point{3, 3}, Magic::Point{3, 2}, Magic::Point{3, 1},
        Magic::Point{4, 4}, Magic::Point{4, 3}, Magic::Point{4, 2},
        Magic::Point{5, 5}, Magic::Point{5, 4}, Magic::Point{5, 3}
};
//constinit auto window4 = magic_points_factory<w4_arr, dimension_inner, 4>();

constexpr array w5_arr = {
        Magic::Point{0, 1},
        Magic::Point{1, 1}, Magic::Point{1, 0}, Magic::Point{1, 2}, 
        Magic::Point{2, 3}, Magic::Point{2, 2}, Magic::Point{2, 1},
        Magic::Point{3, 4}, Magic::Point{3, 3}, Magic::Point{3, 2},
        Magic::Point{4, 5}, Magic::Point{4, 4}, Magic::Point{4, 3},
        Magic::Point{5, 5}, Magic::Point{5, 4}
    };
//constinit auto window5 = magic_points_factory<w5_arr, dimension_inner, 5>();

constexpr array w6_arr = {
        Magic::Point{0, 1},
        Magic::Point{1, 3}, Magic::Point{1, 2}, Magic::Point{1, 1}, Magic::Point{1, 0},
        Magic::Point{2, 4}, Magic::Point{2, 3}, Magic::Point{2, 2}, Magic::Point{2, 1}, Magic::Point{2, 0},
        Magic::Point{3, 5}, Magic::Point{3, 4}, Magic::Point{3, 3}, Magic::Point{3, 2}, Magic::Point{3, 1},
        Magic::Point{4, 5}, Magic::Point{4, 4},
        Magic::Point{5, 5}
};
//constinit auto window6 = magic_points_factory<w6_arr, dimension_inner, 6>();

constexpr array w7_arr = {
        Magic::Point{0, 1},
        Magic::Point{1, 4}, Magic::Point{1, 3}, Magic::Point{1, 2}, Magic::Point{1, 1}, Magic::Point{1, 0},
        Magic::Point{2, 5}, Magic::Point{2, 4}, Magic::Point{2, 3}, Magic::Point{2, 2}, Magic::Point{2, 1}, Magic::Point{2, 0},
        Magic::Point{3, 5}, Magic::Point{3, 4},
        Magic::Point{4, 5}
};
//constinit auto window7 = magic_points_factory<w7_arr, dimension_inner, 7>();

constexpr array w8_arr = {
        Magic::Point{0, 4}, Magic::Point{0, 3}, Magic::Point{0, 2}, Magic::Point{0, 1},
        Magic::Point{1, 5}, Magic::Point{1, 4}, Magic::Point{1, 3}, Magic::Point{1, 2}, Magic::Point{1, 1}, Magic::Point{1, 0},
        Magic::Point{2, 5}, Magic::Point{2, 4}, Magic::Point{2, 3},
        Magic::Point{3, 5}
};
//constinit auto window8 = magic_points_factory<w8_arr, dimension_inner, 8>();

constexpr array w9_arr = {
        Magic::Point{0, 5}, Magic::Point{0, 4}, Magic::Point{0, 3}, Magic::Point{0, 2}, Magic::Point{0, 1},
        Magic::Point{1, 5}, Magic::Point{1, 4}, Magic::Point{1, 3}, Magic::Point{1, 2}, Magic::Point{1, 1}, Magic::Point{1, 0}, Magic::Point{1, -1}, 
        Magic::Point{2, 5}, Magic::Point{2, 4}, Magic::Point{2, 3}
};
//constinit auto window9 = magic_points_factory<w9_arr, dimension_inner, 9>();


//auto all_windows = tie(window0, window1, window2, window3, window4, window5, window6, window7, window8, window9);
auto hardcoded_windows = tie(w0_arr, w1_arr, w2_arr, w3_arr, w4_arr, w5_arr, w6_arr, w7_arr, w8_arr, w9_arr);
