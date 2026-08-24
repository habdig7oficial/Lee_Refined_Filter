/* Hardcoded dimensionxdimension window, create a function that generates this later */

#include "array"
#include "utility"
#include "ranges"

#include "vector"


#include "tuple"
#include "2d_bitset.hpp"
#include "point.hpp"
#include "optimization.hpp" 


#if defined(__clang__)
    #if __cplusplus < 202603L
        #include "../../vendor/gcem/include/gcem.hpp"
        #define CONSTEXP_SUPPORT 0

    #else
        #define CONSTEXP_SUPPORT 1
    #endif
    #else 
        #define CONSTEXP_SUPPORT 1
#endif

using namespace std;
using namespace env;
using namespace Magic;

class MagicPoints {
    private:
        
        #if CONSTEXP_SUPPORT == 1
            static constexpr size_t N = (int)ceil(sqrt(2) * (dimension / 2) * thickness);
        #else
            static constexpr size_t N = (int)gcem::ceil(gcem::sqrt(2) * (dimension / 2) * thickness);
        #endif

        array<Point, N>relative_coordinates = {};
        //const array<Point, M> relevant_points; 

        //BitSetMask<dimension> mask;

        uint side, area;
        uint win_number;
        double win_angle;

        uint win_end;

    public:


    constexpr MagicPoints(int win_number, const array<Point, N>& rl, int side) : relative_coordinates(rl) {
        this -> win_number = win_number;
        this -> side = dimension;
        this -> area = this -> side * this -> side;
    }
    
    constexpr MagicPoints(uint win_number, uint side, uint dim = dimension) : win_number(win_number), side(dimension), area(side * side), win_end(0), win_angle(MagicPoints::angle(win_number)){

        #if CONSTEXP_SUPPORT == 1
            double s = sin(win_angle);
            double c = cos(win_angle);

        #else
            double s = gcem::sin(win_angle);
            double c = gcem::cos(win_angle);
        #endif

        int center = dimension / 2;
        for(int y = -center; y <= center; y++){
            double yc = y * c;
            for(int x = -center; x <= center; x++){
                double xs = x * s;


                #if CONSTEXP_SUPPORT == 1
                    double res = abs(xs - yc);
                #else
                    double res = gcem::abs(xs - yc);
                #endif


                if(res <= thickness / 2 && x >= 0){
                    /* Side A  NOT_ROTATED*/
                    //mask[center - x, center + y] = true;
                    //mask[center + y, center - x] = true;
                    this -> relative_coordinates[win_end++] = Point{(signed char)x, (signed char)y};
                }
            }
        }
    }

    static constexpr double angle(uint win_number, uint dim = dimension) {
        return win_number * numbers::pi / (2 * (dim - 1));
    }
    
    static constexpr uint num_windows(uint dim = dimension){
        return 2 * (dim - 1);
    }


    template<size_t Dim = dimension>
    static constexpr BitSetMask<Dim> gen_mask(double angle, double threshold){
        BitSetMask<Dim> mask {};

            #if CONSTEXP_SUPPORT == 1
                double s = sin(angle);
                double c = cos(angle);
            #else
                double s = gcem::sin(angle);
                double c = gcem::cos(angle);
            #endif

            int center = Dim / 2;
            for(int y = -center; y <= center; y++){
                double yc = y * c;
                for(int x = -center; x <= center; x++){
                    double xs = x * s;


                    #if CONSTEXP_SUPPORT == 1
                        double res = abs(xs - yc);
                    #else
                        double res = gcem::abs(xs - yc);
                    #endif

                    if(res <= threshold / 2){
                        /* Side A  NOT_ROTATED*/
                        mask[center - x, center + y] = true;
                        //mask[center + y, center - x] = true;
                        //mask.push_back(Point{x, y});
                    }
                }
            }

        return mask;
    }

    
    static constexpr tuple<array<Point, N>, size_t> vec_mask(double angle, double threshold = thickness){
	array<Point, N> mask {};

        size_t mask_size = 0;

        #if CONSTEXP_SUPPORT == 1
            double s = sin(angle);
            double c = cos(angle);

        #else
            double s = gcem::sin(angle);
            double c = gcem::cos(angle);
        #endif

        int center = dimension / 2;
        for(int y = -center; y <= center; y++){
            double yc = y * c;
            for(int x = -center; x <= center; x++){
                double xs = x * s;


                #if CONSTEXP_SUPPORT == 1
                    double res = abs(xs - yc);
                #else
                    double res = gcem::abs(xs - yc);
                #endif


                if(res <= threshold / 2 && x >= 0){
                    /* Side A  NOT_ROTATED*/
                    //mask[center - x, center + y] = true;
                    //mask[center + y, center - x] = true;
                    mask[mask_size++] = Point{(signed char)x, (signed char)y};
                }
            }
        }

        return {mask, mask_size};
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
    void traverse_relevant(Lambda lambda){}
        template<typename Lambda>
    void traverse_relevant_inverse(Lambda lambda){}
    /*
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
    }*/

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

    double angle() const {
        return MagicPoints::angle(this -> get_win_num());
    }

    /* Angle of the mirror image */
    double angle_inverse() const {
        return MagicPoints::angle(get_mirror_num());
    }

    size_t size() const {
        return this -> relative_coordinates.size() * 2 + 1; /* Point (0,0) is not counted and the used points is folded */
    }

    int unused() const { 
        return this -> area - this -> size(); 
    }

    uint end()       const { return this -> win_end; }
    int get_side()       const { return this -> side; }
    int get_area()       const { return this -> area; }
    int get_win_num()    const { return this -> win_number; }
    int get_mirror_num() const { return this -> win_number + (dimension - 1); }

    //BitSetMask<dimension> get_mask() const { return this -> mask; } 

    Point constexpr operator [] (uint pos) const {
        return this -> relative_coordinates[pos];
    }

    const Point* get_relevant() const { return NULL; }
    //const Point* get_relevant() const { return relevant_points.data(); }
    //size_t get_relevant_size()  const { return M; }

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

    return MagicPoints(WinNumber, sort_compile_time(RelativeCoordinates, sorting_lambda), Side);
}

template<typename T, size_t N>
constexpr array<T, N> all_angles(){
    constexpr size_t angle_size = MagicPoints::num_windows(dimension);
    array<T,  N> new_arr;
    for(int i = 0; i < N; i++)
        new_arr[i] = MagicPoints::angle(i);
    return new_arr;
};

/*
constexpr size_t masks_size = MagicPoints::num_windows(dimension) / 2;
constexpr array<MagicPoints, masks_size> magic_points_arr(){
  array<MagicPoints, masks_size> masks;

  for(int i = 0; i < masks_size; i++){
    //masks[i] = MagicPoints::gen_mask<dimension>(MagicPoints::angle(i, dimension), thickness);
    MagicPoints(i, dimension_inner);
  }

  return masks;
}
*/

/*
constexpr array w0_arr = {
        Point{0, 1}, 
        Point{1, 1}, Point{1, 0}, Point{1, -1},
        Point{2, 1}, Point{2, 0}, Point{2, -1},
        Point{3, 1}, Point{3, 0}, Point{3, -1},
        Point{4, 1}, Point{4, 0}, Point{4, -1},
        Point{5, 1}, Point{5, 0}, Point{5, -1}
};
constinit auto window0 = magic_points_factory<w0_arr, dimension_inner, 0>();

constexpr array w1_arr = {
        Point{1, -1}, Point{0, 1},
        Point{1, 1}, Point{1, 0},
        Point{2, 2}, Point{2, 1}, Point{2, 0},
        Point{3, 2}, Point{3, 1}, Point{3, 0},
        Point{4, 2}, Point{4, 1}, Point{4, 0},
        Point{5, 2}, Point{5, 1}, Point{5, 0}, 
};
constinit auto window1 = magic_points_factory<w1_arr, dimension_inner, 1>();

constexpr array w2_arr = {
        Point{0, 1},
        Point{1, 1}, Point{1, 0}, Point{1, -1},
        Point{2, 2}, Point{2, 1}, Point{2, 0},
        Point{3, 2}, Point{3, 1},
        Point{4, 3}, Point{4, 2}, Point{4, 1},
        Point{5, 3}, Point{5, 2}, Point{5, 1}
    };
constinit auto window2 = magic_points_factory<w2_arr, dimension_inner, 2>();

constexpr array w3_arr = {
        Point{0, 1}, Point{-1, 1}, 
        Point{1, 1}, Point{1, 0},
        Point{2, 2}, Point{2, 1}, Point{2, 0},
        Point{3, 2}, Point{3, 1},
        Point{4, 3}, Point{4, 2}, Point{4, 1},
        Point{5, 4}, Point{5, 3}, Point{5, 2}
};
constinit auto window3 = magic_points_factory<w3_arr, dimension_inner, 3>();

constexpr array w4_arr = {
        Point{0, 1}, 
        Point{1, 1}, Point{1, 0}, Point{1, -1},
        Point{2, 2}, Point{2, 1}, Point{2, 0},
        Point{3, 3}, Point{3, 2}, Point{3, 1},
        Point{4, 4}, Point{4, 3}, Point{4, 2},
        Point{5, 5}, Point{5, 4}, Point{5, 3}
};
constinit auto window4 = magic_points_factory<w4_arr, dimension_inner, 4>();

constexpr array w5_arr = {
        Point{0, 1},
        Point{1, 1}, Point{1, 0}, Point{1, 2}, 
        Point{2, 3}, Point{2, 2}, Point{2, 1},
        Point{3, 4}, Point{3, 3}, Point{3, 2},
        Point{4, 5}, Point{4, 4}, Point{4, 3},
        Point{5, 5}, Point{5, 4}
    };
constinit auto window5 = magic_points_factory<w5_arr, dimension_inner, 5>();

constexpr array w6_arr = {
        Point{0, 1},
        Point{1, 3}, Point{1, 2}, Point{1, 1}, Point{1, 0},
        Point{2, 4}, Point{2, 3}, Point{2, 2}, Point{2, 1}, Point{2, 0},
        Point{3, 5}, Point{3, 4}, Point{3, 3}, Point{3, 2}, Point{3, 1},
        Point{4, 5}, Point{4, 4},
        Point{5, 5}
};
constinit auto window6 = magic_points_factory<w6_arr, dimension_inner, 6>();

constexpr array w7_arr = {
        Point{0, 1},
        Point{1, 4}, Point{1, 3}, Point{1, 2}, Point{1, 1}, Point{1, 0},
        Point{2, 5}, Point{2, 4}, Point{2, 3}, Point{2, 2}, Point{2, 1}, Point{2, 0},
        Point{3, 5}, Point{3, 4},
        Point{4, 5}
};
constinit auto window7 = magic_points_factory<w7_arr, dimension_inner, 7>();

constexpr array w8_arr = {
        Point{0, 4}, Point{0, 3}, Point{0, 2}, Point{0, 1},
        Point{1, 5}, Point{1, 4}, Point{1, 3}, Point{1, 2}, Point{1, 1}, Point{1, 0},
        Point{2, 5}, Point{2, 4}, Point{2, 3},
        Point{3, 5}
};
constinit auto window8 = magic_points_factory<w8_arr, dimension_inner, 8>();

constexpr array w9_arr = {
        Point{0, 5}, Point{0, 4}, Point{0, 3}, Point{0, 2}, Point{0, 1},
        Point{1, 5}, Point{1, 4}, Point{1, 3}, Point{1, 2}, Point{1, 1}, Point{1, 0}, Point{1, -1}, 
        Point{2, 5}, Point{2, 4}, Point{2, 3}
};
constinit auto window9 = magic_points_factory<w9_arr, dimension_inner, 9>();


auto all_windows = tie(window0, window1, window2, window3, window4, window5, window6, window7, window8, window9);
*/
/*
constexpr array w0_arr = {
        Point{0, 1}, 
        Point{1, 1}, Point{1, 0}, Point{1, -1},
        Point{2, 1}, Point{2, 0}, Point{2, -1},
        Point{3, 1}, Point{3, 0}, Point{3, -1},
        Point{4, 1}, Point{4, 0}, Point{4, -1},
        Point{5, 1}, Point{5, 0}, Point{5, -1}
};

constinit auto window0 = MagicPoints(0, w0_arr, dimension_inner);

*/

auto all_windows = tie();
constexpr size_t all_windows_size = tuple_size_v<decltype(all_windows)>;


constexpr array<double, MagicPoints::num_windows(dimension / 2 + dimension % 2)> angles = all_angles<double, MagicPoints::num_windows(dimension / 2 + dimension % 2)>();






//array<MagicPointsWrapper, 10> all_windows = { window0, window1, window2, window3, window4, window5, window6, window7, window8, window9 };
