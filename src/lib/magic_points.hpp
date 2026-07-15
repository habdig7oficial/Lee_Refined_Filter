/* Hardcoded 11x11 window, create a function that generates this later */

#include "vector"
#include "utility"

using namespace std;
using Point = pair<char, char>;

#define SIDE_A true
#define SIDE_B false


#define NOT_ROTATED true
#define ROTATED false


class MagicPoints {
    public:
        vector<Point>relative_coordinates;
        vector<Point> special_first_column;

    MagicPoints(vector<Point> relative_coordinates, vector<Point> special_first_column){
        this -> relative_coordinates = relative_coordinates;
        this -> special_first_column = special_first_column;
    }

    /* 
        Lambda type should be:
            char (relative x), char (relative y), bool scope(inverted or original)
    */
    template<typename Lambda>
    void traverse(Lambda lambda){
        for(Point spoint : special_first_column){
            cout << "Special: ";
            lambda(spoint.first, spoint.second, SIDE_A);
        }

        for(Point point : relative_coordinates){
            cout << "SIDE_A: ";
            lambda(point.first, point.second, SIDE_A);
            cout << "SIDE_B: ";
            lambda(-point.first, -point.second, SIDE_B);
        }
        
    }

    template<typename Lambda>
    void traverse_inverse(Lambda lambda){
        for(Point spoint : special_first_column){
            cout << "Side A Special: ";
            lambda(spoint.second, spoint.first, SIDE_A);
        }

        for(Point point : relative_coordinates){
            cout << "Side A: ";
            lambda(point.second, point.first, SIDE_A);
            cout << "Side B: ";
            lambda(-point.second, -point.first, SIDE_B);
        }
        
    }

    template<typename Lambda>
    void traverse_both(Lambda lambda){
        for(Point spoint : special_first_column){
            cout << "Side A Special: ";
            lambda(spoint.first, spoint.second, SIDE_A, NOT_ROTATED);
            cout << "Side B Special: ";
            lambda(spoint.second, spoint.first, SIDE_A, ROTATED);
        }

        for(Point point : relative_coordinates){
            cout << "SIDE_A: ";
            lambda(point.first, point.second, SIDE_A, NOT_ROTATED);
            cout << "SIDE_B: ";
            lambda(-point.first, -point.second, SIDE_B, NOT_ROTATED);

            cout << "SIDE_A: ";
            lambda(point.second, point.first, SIDE_A, ROTATED);
            cout << "SIDE_B: ";
            lambda(-point.second, -point.first, SIDE_B, ROTATED);
        }
        
    }

    friend ostream& operator << (ostream& os, const MagicPoints& magic_points){

        os << "Magic Points: [";
        for(Point point : magic_points.special_first_column){
            os << "("<< (int) point.first << ", " << (int) point.second << "),";
        }
        for(Point point : magic_points.relative_coordinates){
            os << "("<< (int) point.first << ", " << (int) point.second << "),";
        }
        os << "]" << endl;

        return os;
    }
};

auto myLambda = [](int x) { 
    std::cout << "Value: " << x << std::endl; 
};

// ok
MagicPoints window0(
    vector<Point>{
        {0, 1},
        {1, 1}, {1, 0}, {1, -1},
        {2, 1}, {2, 0}, {2, -1},
        {3, 1}, {3, 0}, {3, -1},
        {4, 1}, {4, 0}, {4, -1},
        {5, 1}, {5, 0}, {5, -1}

    }, 
    vector<Point>{
        {0, 0}
    }
);


MagicPoints window1(
    vector<Point>{
        {1, -1}, {0, 1},
        {1, 1}, {1, 0},
        {2, 2}, {2, 1}, {2, 0},
        {3, 2}, {3, 1}, {3, 0},
        {4, 2}, {4, 1}, {4, 0},
        {5, 2}, {5, 1}, {5, 0}, 
    }, 
    vector<Point>{
        {0, 0}
    }
);

MagicPoints window2(
    vector<Point>{
        {0, 1},
        {1, 1}, {1, 0}, {1, -1},
        {2, 2}, {2, 1}, {2, 0},
        {3, 2}, {3, 1},
        {4, 3}, {4, 2}, {4, 1},
        {5, 3}, {5, 2}, {5, 1}   
    }, 
    vector<Point>{
        {0, 0}
    }
);

vector<MagicPoints> all_windows = {window0, window1, window2};