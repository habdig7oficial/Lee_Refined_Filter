/* Hardcoded DIMENSIONxDIMENSION window, create a function that generates this later */

#include "array"
#include "utility"
#include "ranges"


#include "tuple"
#include "2d_bitset.hpp"
#include "point.hpp"
#include "optimization.hpp" 


using namespace std;
using namespace env;
using namespace Magic;

template <size_t N, size_t M>
class MagicPoints {
    private:
        const array<Point, N>relative_coordinates;
        const array<Point, M> relevant_points; 

        BitSetMask<DIMENSION> mask;

        int side, area;
        int win_number;

    public:
    constexpr MagicPoints(int win_number, const array<Point, N>& rl, int side) : relative_coordinates(rl), relevant_points{ gen_static<N, M>(rl, side) }, mask(BitSetMask<DIMENSION>(relevant_points, rl)) {
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

    const BitSetMask<DIMENSION>& get_mask() const { return this -> mask; } 

    const Point* get_relevant() const { return relevant_points.data(); }
    size_t get_relevant_size()  const { return M; }

    #if !NDEBUG  
        vector<Point> show_marked(){ return mark_relevant(relative_coordinates); }
        vector<Point> show_filtered(){ return filter(this -> show_marked(), 3); }
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

template<array RelativeCoordinates, uint Side, uint WinNumber>
constexpr auto magic_points_factory(){
    constexpr size_t N = RelativeCoordinates.size();
    constexpr size_t M = filtered_size(RelativeCoordinates, Side);

    auto relevant_points = gen_static<N, M>(RelativeCoordinates, Side);

    return MagicPoints<N, M>(WinNumber, sort_compile_time(RelativeCoordinates, sorting_lambda), Side);
}

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
};

constexpr array w0_arr = {
        Point{0, 1}, 
        Point{1, 1}, Point{1, 0}, Point{1, -1},
        Point{2, 1}, Point{2, 0}, Point{2, -1},
        Point{3, 1}, Point{3, 0}, Point{3, -1},
        Point{4, 1}, Point{4, 0}, Point{4, -1},
        Point{5, 1}, Point{5, 0}, Point{5, -1}
};
constinit auto window0 = magic_points_factory<w0_arr, DIMENSION_INNER, 0>();

constexpr array w1_arr = {
        Point{1, -1}, Point{0, 1},
        Point{1, 1}, Point{1, 0},
        Point{2, 2}, Point{2, 1}, Point{2, 0},
        Point{3, 2}, Point{3, 1}, Point{3, 0},
        Point{4, 2}, Point{4, 1}, Point{4, 0},
        Point{5, 2}, Point{5, 1}, Point{5, 0}, 
};
constinit auto window1 = magic_points_factory<w1_arr, DIMENSION_INNER, 1>();

constexpr array w2_arr = {
        Point{0, 1},
        Point{1, 1}, Point{1, 0}, Point{1, -1},
        Point{2, 2}, Point{2, 1}, Point{2, 0},
        Point{3, 2}, Point{3, 1},
        Point{4, 3}, Point{4, 2}, Point{4, 1},
        Point{5, 3}, Point{5, 2}, Point{5, 1}
    };
constinit auto window2 = magic_points_factory<w2_arr, DIMENSION_INNER, 2>();

constexpr array w3_arr = {
        Point{0, 1}, Point{-1, 1}, 
        Point{1, 1}, Point{1, 0},
        Point{2, 2}, Point{2, 1}, Point{2, 0},
        Point{3, 2}, Point{3, 1},
        Point{4, 3}, Point{4, 2}, Point{4, 1},
        Point{5, 4}, Point{5, 3}, Point{5, 2}
};
constinit auto window3 = magic_points_factory<w3_arr, DIMENSION_INNER, 3>();

constexpr array w4_arr = {
        Point{0, 1}, 
        Point{1, 1}, Point{1, 0}, Point{1, -1},
        Point{2, 2}, Point{2, 1}, Point{2, 0},
        Point{3, 3}, Point{3, 2}, Point{3, 1},
        Point{4, 4}, Point{4, 3}, Point{4, 2},
        Point{5, 5}, Point{5, 4}, Point{5, 3}
};
constinit auto window4 = magic_points_factory<w4_arr, DIMENSION_INNER, 4>();

constexpr array w5_arr = {
        Point{0, 1},
        Point{1, 1}, Point{1, 0}, Point{1, 2}, 
        Point{2, 3}, Point{2, 2}, Point{2, 1},
        Point{3, 4}, Point{3, 3}, Point{3, 2},
        Point{4, 5}, Point{4, 4}, Point{4, 3},
        Point{5, 5}, Point{5, 4}
    };
constinit auto window5 = magic_points_factory<w5_arr, DIMENSION_INNER, 5>();

constexpr array w6_arr = {
        Point{0, 1},
        Point{1, 3}, Point{1, 2}, Point{1, 1}, Point{1, 0},
        Point{2, 4}, Point{2, 3}, Point{2, 2}, Point{2, 1}, Point{2, 0},
        Point{3, 5}, Point{3, 4}, Point{3, 3}, Point{3, 2}, Point{3, 1},
        Point{4, 5}, Point{4, 4},
        Point{5, 5}
};
constinit auto window6 = magic_points_factory<w6_arr, DIMENSION_INNER, 6>();

constexpr array w7_arr = {
        Point{0, 1},
        Point{1, 4}, Point{1, 3}, Point{1, 2}, Point{1, 1}, Point{1, 0},
        Point{2, 5}, Point{2, 4}, Point{2, 3}, Point{2, 2}, Point{2, 1}, Point{2, 0},
        Point{3, 5}, Point{3, 4},
        Point{4, 5}
};
constinit auto window7 = magic_points_factory<w7_arr, DIMENSION_INNER, 7>();

constexpr array w8_arr = {
        Point{0, 4}, Point{0, 3}, Point{0, 2}, Point{0, 1},
        Point{1, 5}, Point{1, 4}, Point{1, 3}, Point{1, 2}, Point{1, 1}, Point{1, 0},
        Point{2, 5}, Point{2, 4}, Point{2, 3},
        Point{3, 5}
};
constinit auto window8 = magic_points_factory<w8_arr, DIMENSION_INNER, 8>();

constexpr array w9_arr = {
        Point{0, 5}, Point{0, 4}, Point{0, 3}, Point{0, 2}, Point{0, 1},
        Point{1, 5}, Point{1, 4}, Point{1, 3}, Point{1, 2}, Point{1, 1}, Point{1, 0}, Point{1, -1}, 
        Point{2, 5}, Point{2, 4}, Point{2, 3}
};
constinit auto window9 = magic_points_factory<w9_arr, DIMENSION_INNER, 9>();


auto all_windows = tie(window0, window1, window2, window3, window4, window5, window6, window7, window8, window9);
constexpr size_t all_windows_size = tuple_size_v<decltype(all_windows)>;

array<double, 2 * all_windows_size> angles = all_angles<double, 2 * all_windows_size>(all_windows);




//array<MagicPointsWrapper, 10> all_windows = { window0, window1, window2, window3, window4, window5, window6, window7, window8, window9 };