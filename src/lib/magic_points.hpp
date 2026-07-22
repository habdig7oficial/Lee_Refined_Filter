/* Hardcoded DIMENSIONxDIMENSION window, create a function that generates this later */

#include "array"
#include "utility"

#include "tuple"
#include "optimization.hpp" 

using namespace std;
using namespace env;
using Point = pair<char, char>;

#define DIMENSION 11
#define DIMENSION_INNER 3

#define INNER_HALF (int) DIMENSION_INNER / 2
#define INNER_AREA DIMENSION_INNER * DIMENSION_INNER
#define RELEVANT_POINTS_SIZE 2 * INNER_AREA * (N + 1)

#define SIDE_A true
#define SIDE_B false


#define NOT_ROTATED true
#define ROTATED false


template <size_t N>
class MagicPoints {
    private:
        const array<Point, N>relative_coordinates;
        const array<Point, RELEVANT_POINTS_SIZE>relevant_points; 
        int side, area;
        int win_number;

    public:
    MagicPoints(int win_number, const array<Point, N>& relative_coordinates, int side) : relative_coordinates(relative_coordinates), relevant_points(this -> mark_relevant()){
        this -> win_number = win_number;
        this -> side = side;
        this -> area = this -> side * this -> side;

        this -> filter(this -> mark_relevant(), DIMENSION_INNER);
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
    void traverse_data(Lambda lambda){
        if constexpr (dev_mode)
            cout << "Side A Special: ";
            
        lambda(0, 0, SIDE_A);

        if constexpr (dev_mode)
            cout << "SIDE_A: ";
        for(const Point& point : this -> relative_coordinates)
            lambda(point.first, point.second, SIDE_A);

    }

    template<typename T, size_t M> 
    constexpr size_t filter_size(array<T, M> arr, uint threshold){
        size_t matches = 0;
        typename array<T, M>::iterator new_end, point;
        new_end = arr.end();

        for(point = arr.begin(); point != new_end; ++point){
            int c = count(arr.begin(), new_end, *point);

            if(c < threshold){
               new_end = remove(arr.begin(), new_end, *point);
               matches++;
               continue;
            }
        }
        return matches;
    }

    template<typename T, size_t M> 
    constexpr vector<T> filter(array<T, M> arr, uint threshold){

        vector<T> new_vec;
        typename array<T, M>::iterator new_end, point;

        new_end = arr.end();
        for(point = arr.begin(); point != new_end; ++point){
            int c = count(arr.begin(), new_end, *point);

            if(c < threshold){
               new_end = remove(arr.begin(), new_end, *point);
               continue;
            }

            cout << "(" << (int)point -> first << ", " << (int)point -> second << ") " << c << endl;
        }

        copy(arr.begin(), new_end, back_inserter(new_vec));

        sort(new_vec.begin(), new_vec.end());
        
        auto cleaned = unique(new_vec.begin(), new_vec.end());
        new_vec.erase(cleaned, new_vec.end());
        

        cout << " <<<<<<<<<<<>>>>>>>>>>>>>>>> " << endl;

       for(const Point& point : new_vec)
           cout << "(" << (int)point.first << ", " << (int)point.second << ") " << count(new_vec.begin(), new_vec.end(), point) << endl;

        cout << new_vec.size() << endl;

        return new_vec;
    }

    constexpr array<Point, RELEVANT_POINTS_SIZE> mark_relevant(){
        array<Point, RELEVANT_POINTS_SIZE> relevant_points;

        if(dev_mode)
            cout << this -> get_win_num() << ") " << endl;

        int c = 0;
        this -> traverse([&c, &relevant_points](char rx, char ry, bool scope){
            for(int j = ry - INNER_HALF; j <= ry + INNER_HALF; j++){
                for(int i = rx - INNER_HALF; i <= rx + INNER_HALF; i++){
                    if(dev_mode){
                        cout << "this -> (" << (int)rx << ", " << (int)ry << ") |\t";
                        cout << "(" << i << ", " << (int)j << ") - " << c << endl;

                        /* Cap out of bounds points */
                        if(abs(i) > (int) DIMENSION / 2 || abs(j) > (int) DIMENSION / 2){
                            relevant_points[c] = Point{0, 0};
                            continue;
                        }
    
                        relevant_points[c] = Point{i, j};
                        c++;
                    }
                }
                if(dev_mode)
                    cout << endl << " --(j)-- " << endl;
            }
            if(dev_mode)
                cout << endl << " --(i)-- " << endl;
        });

        cout << " ===================================== " << endl;
        return relevant_points;
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

    friend ostream& operator << (ostream& os, const MagicPoints& magic_points){
        os << "Magic Points: [";
        for(const Point& point : magic_points.relative_coordinates){
            os << "("<< (int) point.first << ", " << (int) point.second << "),";
        }
        os << "]" << endl;

        return os;
    }
};

auto sorting_lambda = [](const Point& a, const Point &b){
    if(a.second == b.second){
        return a.first < b.first;
    }
    else
        return a.second > b.second;
};


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

auto all_windows = tie(window0, window1, window2, window3, window4, window5, window6, window7, window8, window9);
constexpr size_t all_windows_size = tuple_size_v<decltype(all_windows)>;

array<double, 2 * all_windows_size> angles = all_angles<double, 2 * all_windows_size>(all_windows);




//array<MagicPointsWrapper, 10> all_windows = { window0, window1, window2, window3, window4, window5, window6, window7, window8, window9 };