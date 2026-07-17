/* Hardcoded 11x11 window, create a function that generates this later */

#include "array"
#include "utility"

#include "tuple"
#include "optimization.hpp" 

using namespace std;
using Point = pair<char, char>;

#define SIDE_A true
#define SIDE_B false


#define NOT_ROTATED true
#define ROTATED false


template <size_t N>
class MagicPoints {
    private:
        const array<Point, N>relative_coordinates;
        int side, area;

    public:
    MagicPoints(const array<Point, N>& relative_coordinates, int side) : relative_coordinates(relative_coordinates){
        this -> side = side;
        this -> area = this -> side * this -> side;
    }

    /* 
        Lambda type should be:
            char (relative x), char (relative y), bool scope(inverted or original)
    */
    template<typename Lambda>
    void traverse(Lambda lambda){
        cout << "Side A Special: ";
        lambda(0, 0, SIDE_A);

        cout << "SIDE_A: ";
        for(const Point& point : this -> relative_coordinates)
            lambda(point.first, point.second, SIDE_A);

        cout << "SIDE_B: ";
        for(const Point& point : this -> relative_coordinates)
            lambda(-point.first, -point.second, SIDE_B);
    }


    template<typename Lambda>
    void traverse_inverse(Lambda lambda){
        cout << "Side A Special: ";
        lambda(0, 0, SIDE_A);
    
        cout << "SIDE_A: ";
        for(const Point& point : this -> relative_coordinates)
            lambda(-point.second, point.first, SIDE_A);
        
        cout << "SIDE_B: ";
        for(const Point& point : this -> relative_coordinates)
            lambda(point.second, -point.first, SIDE_B);
    }

    template<typename Lambda>
    void traverse_both(Lambda lambda){
        cout << "Side A Special: ";
        lambda(0, 0, SIDE_A, NOT_ROTATED);
        cout << "Side B Special: ";
        lambda(0, 0, SIDE_A, ROTATED);

        for(const Point& point : this -> relative_coordinates){
            cout << "SIDE_A NOT_ROTATED: ";
            lambda(point.first, point.second, SIDE_A, NOT_ROTATED);
            cout << "SIDE_B NOT_ROTATED: ";
            lambda(-point.first, -point.second, SIDE_B, NOT_ROTATED);

            cout << "SIDE_A ROTATED: ";
            lambda(-point.second, point.first, SIDE_A, ROTATED);
            cout << "SIDE_A ROTATED: ";
            lambda(point.second, -point.first, SIDE_B, ROTATED);
        }
        
    }

    size_t size() const {
        return this -> relative_coordinates.size() * 2 + 1; /* Point (0,0) is not counted and the used points is folded */
    }

    int unused() const { 
        return this -> area - this -> size(); 
    }

    int get_side() const { return this -> side; }
    int get_area() const { return this -> area; }

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
    sort_compile_time(array<Point, 16>{
        Point{0, 1}, 
        Point{1, 1}, Point{1, 0}, Point{1, -1},
        Point{2, 1}, Point{2, 0}, Point{2, -1},
        Point{3, 1}, Point{3, 0}, Point{3, -1},
        Point{4, 1}, Point{4, 0}, Point{4, -1},
        Point{5, 1}, Point{5, 0}, Point{5, -1}
    }, sorting_lambda),
    11
);


MagicPoints window1(
    sort_compile_time(array<Point, 16>{
        Point{1, -1}, Point{0, 1},
        Point{1, 1}, Point{1, 0},
        Point{2, 2}, Point{2, 1}, Point{2, 0},
        Point{3, 2}, Point{3, 1}, Point{3, 0},
        Point{4, 2}, Point{4, 1}, Point{4, 0},
        Point{5, 2}, Point{5, 1}, Point{5, 0}, 
    }, sorting_lambda),   
    11
);

MagicPoints window2(
    sort_compile_time(array<Point, 15>{
        Point{0, 1},
        Point{1, 1}, Point{1, 0}, Point{1, -1},
        Point{2, 2}, Point{2, 1}, Point{2, 0},
        Point{3, 2}, Point{3, 1},
        Point{4, 3}, Point{4, 2}, Point{4, 1},
        Point{5, 3}, Point{5, 2}, Point{5, 1}
    }, sorting_lambda),  
    11
);

MagicPoints window3(
    sort_compile_time(array<Point, 15>{
        Point{0, 1}, Point{-1, 1}, 
        Point{1, 1}, Point{1, 0},
        Point{2, 2}, Point{2, 1}, Point{2, 0},
        Point{3, 2}, Point{3, 1},
        Point{4, 3}, Point{4, 2}, Point{4, 1},
        Point{5, 4}, Point{5, 3}, Point{5, 2}
    }, sorting_lambda),    
    11
);

MagicPoints window4(
    sort_compile_time(array<Point, 16>{
        Point{0, 1}, 
        Point{1, 1}, Point{1, 0}, Point{1, -1},
        Point{2, 2}, Point{2, 1}, Point{2, 0},
        Point{3, 3}, Point{3, 2}, Point{3, 1},
        Point{4, 4}, Point{4, 3}, Point{4, 2},
        Point{5, 5}, Point{5, 4}, Point{5, 3}
    }, sorting_lambda),
    11
);

MagicPoints window5(
    sort_compile_time(array<Point, 15>{
        Point{0, 1},
        Point{1, 1}, Point{1, 0}, Point{1, 2}, 
        Point{2, 3}, Point{2, 2}, Point{2, 1},
        Point{3, 4}, Point{3, 3}, Point{3, 2},
        Point{4, 5}, Point{4, 4}, Point{4, 3},
        Point{5, 5}, Point{5, 4}
    }, sorting_lambda),
    11
);

MagicPoints window6(
    sort_compile_time(array<Point, 18>{
        Point{0, 1},
        Point{1, 3}, Point{1, 2}, Point{1, 1}, Point{1, 0},
        Point{2, 4}, Point{2, 3}, Point{2, 2}, Point{2, 1}, Point{2, 0},
        Point{3, 5}, Point{3, 4}, Point{3, 3}, Point{3, 2}, Point{3, 1},
        Point{4, 5}, Point{4, 4},
        Point{5, 5}
    }, sorting_lambda),
    11
);

MagicPoints window7(
    sort_compile_time(array<Point, 15>{
        Point{0, 1},
        Point{1, 4}, Point{1, 3}, Point{1, 2}, Point{1, 1}, Point{1, 0},
        Point{2, 5}, Point{2, 4}, Point{2, 3}, Point{2, 2}, Point{2, 1}, Point{2, 0},
        Point{3, 5}, Point{3, 4},
        Point{4, 5}
    }, sorting_lambda), 
    11
);

MagicPoints window8(
    sort_compile_time(array<Point, 14>{
        Point{0, 4}, Point{0, 3}, Point{0, 2}, Point{0, 1},
        Point{1, 5}, Point{1, 4}, Point{1, 3}, Point{1, 2}, Point{1, 1}, Point{1, 0},
        Point{2, 5}, Point{2, 4}, Point{2, 3},
        Point{3, 5}
    }, sorting_lambda),
    11
);


MagicPoints window9(
    sort_compile_time(array<Point,15>{
        Point{0, 5}, Point{0, 4}, Point{0, 3}, Point{0, 2}, Point{0, 1},
        Point{1, 5}, Point{1, 4}, Point{1, 3}, Point{1, 2}, Point{1, 1}, Point{1, 0}, Point{1, -1}, 
        Point{2, 5}, Point{2, 4}, Point{2, 3}
    }, sorting_lambda),
    11
);

auto all_windows = tie(window0, window1, window2, window3, window4, window5, window6, window7, window8, window9);
constexpr size_t all_windows_size = tuple_size_v<decltype(all_windows)>;

//array<MagicPointsWrapper, 10> all_windows = { window0, window1, window2, window3, window4, window5, window6, window7, window8, window9 };