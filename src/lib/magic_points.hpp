/* Hardcoded DIMENSIONxDIMENSION window, create a function that generates this later */

#include "array"
#include "utility"
#include "ranges"


#include "tuple"
#include "2d_bitset.hpp"
#include "optimization.hpp" 

using namespace std;
using namespace env;

#define DIMENSION 11
#define DIMENSION_INNER 3

#define INNER_HALF ((int) DIMENSION_INNER / 2)
#define INNER_AREA (DIMENSION_INNER * DIMENSION_INNER)
#define RELEVANT_POINTS_SIZE(N) (2 * INNER_AREA * (N + 1)) 

#define SIDE_A true
#define SIDE_B false


#define NOT_ROTATED true
#define ROTATED false


#if(DIMENSION / 2 <= (SCHAR_MAX >> (CHAR_BIT / 2)))
    #define SIZE_POINT (CHAR_BIT / 2)
#elif(DIMENSION / 2 <= SCHAR_MAX)
    #define SIZE_POINT CHAR_BIT
#endif

/* In side A NOT_ROTATED is (x, y) */
struct Point {
    signed char first : SIZE_POINT;
    signed char second : SIZE_POINT;

    auto operator <=> (const Point&) const = default;
};


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
        for(signed char j = ry - INNER_HALF; j <= ry + INNER_HALF; j++){
            for(signed char i = rx - INNER_HALF; i <= rx + INNER_HALF; i++){

                /* Cap out of bounds points */
                if(const_abs(i) > ((int) DIMENSION / 2) - 1 || const_abs(j) > ((int) DIMENSION / 2) - 1)
                    continue;

                /* Ensure that the mirror points are placed */
                if(rx == 0){
                    for(int k = 0; k < DIMENSION; k++)
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


template <size_t N, size_t M>
class MagicPoints {
    private:
        const array<Point, N>relative_coordinates;
        //vector<Point> relevant_points; 
        array<Point, M> relevant_points; 

        BitSet2D<N, N> mask;

        int side, area;
        int win_number;

    public:
    constexpr MagicPoints(int win_number, const array<Point, N>& rl, int side) : relative_coordinates(rl), relevant_points{ gen_static<N, M>(rl, DIMENSION) } {
        this -> win_number = win_number;
        this -> side = side;
        this -> area = this -> side * this -> side;
    }

    /* 
        Lambda type should be:
            char (relative x), char (relative y), bool scope(inverted or original)
    */
    template<typename Lambda>
    void traverse(Lambda lambda){
        if constexpr (dev_mode)
            cout << "Side A Special: ";
            
        lambda(0, 0, SIDE_A);

        if constexpr (dev_mode)
            cout << "SIDE_A: ";
        for(const Point& point : this -> relative_coordinates)
            lambda(point.first, point.second, SIDE_A);

        if constexpr (dev_mode)
            cout << "SIDE_B: ";
        for(const Point& point : this -> relative_coordinates)
            lambda(-point.first, -point.second, SIDE_B);
    }


    template<typename Lambda>
    void traverse_inverse(Lambda lambda){
        if constexpr (dev_mode)
            cout << "Side A Special: ";
        lambda(0, 0, SIDE_A);
    
        if constexpr (dev_mode)
            cout << "SIDE_A: ";
        for(const Point& point : this -> relative_coordinates)
            lambda(-point.second, point.first, SIDE_A);

        if constexpr (dev_mode)
             cout << "SIDE_B: ";
        for(const Point& point : this -> relative_coordinates)
            lambda(point.second, -point.first, SIDE_B);
    }

    template<typename Lambda>
    void traverse_relevant(Lambda lambda){
        if constexpr (dev_mode)
            cout << "Side A Special: ";
            
        lambda(0, 0, SIDE_A);

        if constexpr (dev_mode)
            cout << "SIDE_A: ";
        for(const Point& point : this -> relevant_points)
            lambda(point.first, point.second, SIDE_A);

        if constexpr (dev_mode)
            cout << "SIDE_B: ";
        for(const Point& point : this -> relevant_points)
            lambda(-point.first, -point.second, SIDE_B);
    }

    template<typename Lambda>
    void traverse_relevant_inverse(Lambda lambda){
        if constexpr (dev_mode)
            cout << "Side A Special: ";
        lambda(0, 0, SIDE_A);
    
        if constexpr (dev_mode)
            cout << "SIDE_A: ";
        for(const Point& point : this -> relevant_points)
            lambda(-point.second, point.first, SIDE_A);

        if constexpr (dev_mode)
             cout << "SIDE_B: ";
        for(const Point& point : this -> relevant_points)
            lambda(point.second, -point.first, SIDE_B);
    }

    template<typename Lambda>
    void traverse_data(Lambda lambda){
        if constexpr (dev_mode)
            cout << "Side A Special: ";
            
        lambda(0, 0, SIDE_A);

        if constexpr (dev_mode)
            cout << "SIDE_A: ";
        for(const Point& point : this -> relative_coordinates)
            lambda(point.first, point.second, SIDE_A);
    }

    /* Numbers of matrixes tiles before complete a half spin */
    int dimension() const {
        return 2 * (this -> side - 1);
    }

    double angle() const {
        return this -> win_number * numbers::pi / this -> dimension();
    }

    /* Angle of the mirror image */
    double angle_inverse() const {
        return this -> get_mirror_num() * numbers::pi / this -> dimension();
    }

    size_t size() const {
        return this -> relative_coordinates.size() * 2 + 1; /* Point (0,0) is not counted and the used points is folded */
    }

    int unused() const { 
        return this -> area - this -> size(); 
    }

    int get_side()       const { return this -> side; }
    int get_area()       const { return this -> area; }
    int get_win_num()    const { return this -> win_number; }
    int get_mirror_num() const { return this -> win_number + (int)(this -> dimension() / 2); }


    #if !NDEBUG  
        vector<Point> show_marked(){ return mark_relevant(relative_coordinates); }
        vector<Point> show_filtered(){ return relevant_points; }
    #endif

    friend ostream& operator << (ostream& os, const MagicPoints& magic_points){
        os << "Magic Points: [";
        for(const Point& point : magic_points.relative_coordinates){
            os << "("<< (int) point.first << ", " << (int) point.second << "),";
        }
        os << "]" << endl;

        return os;
    }
};

template<array RelativeCoordinates, uint Side>
constexpr auto magic_points_factory(int win_number){
    constexpr size_t N = RelativeCoordinates.size();
    constexpr size_t M = filtered_size(RelativeCoordinates, Side);

    auto relevant_points = gen_static<N, M>(RelativeCoordinates, Side);

    return MagicPoints<N, M>(win_number, sort_compile_time(RelativeCoordinates, sorting_lambda), Side);
}


/*
MagicPoints window0(
    0,
    sort_compile_time(array<Point, 16>{
        Point{0, 1}, 
        Point{1, 1}, Point{1, 0}, Point{1, -1},
        Point{2, 1}, Point{2, 0}, Point{2, -1},
        Point{3, 1}, Point{3, 0}, Point{3, -1},
        Point{4, 1}, Point{4, 0}, Point{4, -1},
        Point{5, 1}, Point{5, 0}, Point{5, -1}
    }, sorting_lambda),
    DIMENSION
);


MagicPoints window1(
    1,
    sort_compile_time(array<Point, 16>{
        Point{1, -1}, Point{0, 1},
        Point{1, 1}, Point{1, 0},
        Point{2, 2}, Point{2, 1}, Point{2, 0},
        Point{3, 2}, Point{3, 1}, Point{3, 0},
        Point{4, 2}, Point{4, 1}, Point{4, 0},
        Point{5, 2}, Point{5, 1}, Point{5, 0}, 
    }, sorting_lambda),   
    DIMENSION
);

MagicPoints window2(
    2,
    sort_compile_time(array<Point, 15>{
        Point{0, 1},
        Point{1, 1}, Point{1, 0}, Point{1, -1},
        Point{2, 2}, Point{2, 1}, Point{2, 0},
        Point{3, 2}, Point{3, 1},
        Point{4, 3}, Point{4, 2}, Point{4, 1},
        Point{5, 3}, Point{5, 2}, Point{5, 1}
    }, sorting_lambda),  
    DIMENSION
);

MagicPoints window3(
    3,
    sort_compile_time(array<Point, 15>{
        Point{0, 1}, Point{-1, 1}, 
        Point{1, 1}, Point{1, 0},
        Point{2, 2}, Point{2, 1}, Point{2, 0},
        Point{3, 2}, Point{3, 1},
        Point{4, 3}, Point{4, 2}, Point{4, 1},
        Point{5, 4}, Point{5, 3}, Point{5, 2}
    }, sorting_lambda),    
    DIMENSION
);

MagicPoints window4(
    4,
    sort_compile_time(array<Point, 16>{
        Point{0, 1}, 
        Point{1, 1}, Point{1, 0}, Point{1, -1},
        Point{2, 2}, Point{2, 1}, Point{2, 0},
        Point{3, 3}, Point{3, 2}, Point{3, 1},
        Point{4, 4}, Point{4, 3}, Point{4, 2},
        Point{5, 5}, Point{5, 4}, Point{5, 3}
    }, sorting_lambda),
    DIMENSION
);

MagicPoints window5(
    5,
    sort_compile_time(array<Point, 15>{
        Point{0, 1},
        Point{1, 1}, Point{1, 0}, Point{1, 2}, 
        Point{2, 3}, Point{2, 2}, Point{2, 1},
        Point{3, 4}, Point{3, 3}, Point{3, 2},
        Point{4, 5}, Point{4, 4}, Point{4, 3},
        Point{5, 5}, Point{5, 4}
    }, sorting_lambda),
    DIMENSION
);

MagicPoints window6(
    6,
    sort_compile_time(array<Point, 18>{
        Point{0, 1},
        Point{1, 3}, Point{1, 2}, Point{1, 1}, Point{1, 0},
        Point{2, 4}, Point{2, 3}, Point{2, 2}, Point{2, 1}, Point{2, 0},
        Point{3, 5}, Point{3, 4}, Point{3, 3}, Point{3, 2}, Point{3, 1},
        Point{4, 5}, Point{4, 4},
        Point{5, 5}
    }, sorting_lambda),
    DIMENSION
);

MagicPoints window7(
    7,
    sort_compile_time(array<Point, 15>{
        Point{0, 1},
        Point{1, 4}, Point{1, 3}, Point{1, 2}, Point{1, 1}, Point{1, 0},
        Point{2, 5}, Point{2, 4}, Point{2, 3}, Point{2, 2}, Point{2, 1}, Point{2, 0},
        Point{3, 5}, Point{3, 4},
        Point{4, 5}
    }, sorting_lambda), 
    DIMENSION
);

MagicPoints window8(
    8,
    sort_compile_time(array<Point, 14>{
        Point{0, 4}, Point{0, 3}, Point{0, 2}, Point{0, 1},
        Point{1, 5}, Point{1, 4}, Point{1, 3}, Point{1, 2}, Point{1, 1}, Point{1, 0},
        Point{2, 5}, Point{2, 4}, Point{2, 3},
        Point{3, 5}
    }, sorting_lambda),
    DIMENSION
);


MagicPoints window9(
    9,
    sort_compile_time(array<Point,15>{
        Point{0, 5}, Point{0, 4}, Point{0, 3}, Point{0, 2}, Point{0, 1},
        Point{1, 5}, Point{1, 4}, Point{1, 3}, Point{1, 2}, Point{1, 1}, Point{1, 0}, Point{1, -1}, 
        Point{2, 5}, Point{2, 4}, Point{2, 3}
    }, sorting_lambda),
    DIMENSION
);

*/
template<typename T, size_t N>
constexpr array<T, N> all_angles(auto& all_windows){
    array<T,  N> new_arr;
    int i = 0;
    apply([&i, &new_arr](auto&&... win){
        ((
            new_arr[i] = win.angle(),
            i++
        ), ...);
    }, all_windows);

    apply([&i, &new_arr](auto&&... win){
        ((
            new_arr[i] = win.angle_inverse(),
            i++
        ), ...);
    }, all_windows);
    return new_arr;
}

;

constexpr array w0_arr = {
        Point{0, 1}, 
        Point{1, 1}, Point{1, 0}, Point{1, -1},
        Point{2, 1}, Point{2, 0}, Point{2, -1},
        Point{3, 1}, Point{3, 0}, Point{3, -1},
        Point{4, 1}, Point{4, 0}, Point{4, -1},
        Point{5, 1}, Point{5, 0}, Point{5, -1}
};
auto window0 = magic_points_factory<w0_arr, DIMENSION>(0);
auto all_windows = tie(window0);
//auto all_windows = tie(window0, window1, window2, window3, window4, window5, window6, window7, window8, window9);
constexpr size_t all_windows_size = tuple_size_v<decltype(all_windows)>;

array<double, 2 * all_windows_size> angles = all_angles<double, 2 * all_windows_size>(all_windows);




//array<MagicPointsWrapper, 10> all_windows = { window0, window1, window2, window3, window4, window5, window6, window7, window8, window9 };