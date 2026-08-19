#pragma once

inline constexpr size_t dimension =  11;
inline constexpr size_t dimension_inner = 3;

inline constexpr size_t inner_half = dimension_inner / 2;
inline constexpr size_t inner_area = (dimension_inner * dimension_inner);

inline constexpr size_t size_point = (dimension / 2 <= (SCHAR_MAX >> (CHAR_BIT / 2)))? CHAR_BIT / 2 : CHAR_BIT;

//#define RELEVANT_POINTS_SIZE(N) (2 * INNER_AREA * (N + 1)) 

inline constexpr uint num_windows = 2 * (dimension - 1);

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

template<size_t M>
constexpr vector<Point> mark_relevant(const array<Point, M>arr){
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