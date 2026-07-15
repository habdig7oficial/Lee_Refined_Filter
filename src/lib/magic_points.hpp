/* Hardcoded 11x11 window, create a function that generates this later */

#include "vector"
#include "utility"

using namespace std;
using Point = pair<char, char>;

class MagicPoints {
    public:
        vector<Point>relative_coordinates;
        vector<Point> special_first_column;

    MagicPoints(vector<Point> relative_coordinates, vector<Point> special_first_column){
        this -> relative_coordinates = relative_coordinates;
        this -> special_first_column = special_first_column;
    }

    template<typename Lambda>
    auto traverse(Lambda lambda){
        for(Point spoint : special_first_column){
            cout << "Special: ";
            lambda(spoint.first, spoint.second);
        }

        for(Point point : relative_coordinates){
            cout << "Original: ";
            lambda(point.first, point.second);
            cout << "Inverted: ";
            lambda(-point.first, -point.second);
        }
        return 1;
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

MagicPoints window0(
    vector<Point>{
        {1, 1}, {1, 0}, {1, -1},
        {2, 1}, {2, 0}, {2, -1},
        {3, 1}, {3, 0}, {3, -1},
        {4, 1}, {4, 0}, {4, -1},
        {5, 1}, {5, 0}, {5, -1}

    }, 
    vector<Point>{
        {0, 1}, {0, 0}
    }
);

MagicPoints window1(
    vector<Point>{
        {1, 1}, {1, 0}, {1, -1},
        {2, 2}, {2, 1}, {2, 0},
        {3, 2}, {3, 1}, {3, 0},
        {4, 2}, {4, 1}, {4, 0},
        {5, 2}, {5, 1}, {5, 0}
    }, 
    vector<Point>{
        {0, 1}, {0, 0}
    }
);

MagicPoints window2(
    vector<Point>{
        {1, 1}, {1, 0}, {1, -1},
        {2, 2}, {2, 1}, {2, 0},
        {3, 2}, {3, 1},
        {4, 3}, {4, 2}, {4, 1},
        {5, 3}, {5, 2}, {5, 1}   
    }, 
    vector<Point>{
        {0, 1}, {0, 0}
    }
);

vector<MagicPoints> all_windows = {window0, window1, window2};