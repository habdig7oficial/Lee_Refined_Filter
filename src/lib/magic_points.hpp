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
        int side, area;

    MagicPoints(vector<Point> relative_coordinates, int side){
        this -> relative_coordinates = relative_coordinates;
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

        for(Point point : this -> relative_coordinates){
            cout << "SIDE_A: ";
            lambda(point.first, point.second, SIDE_A);
            cout << "SIDE_B: ";
            lambda(-point.first, -point.second, SIDE_B);
        }
        
    }

    template<typename Lambda>
    void traverse_inverse(Lambda lambda){
        cout << "Side A Special: ";
        lambda(0, 0, SIDE_A);

        for(Point point : this -> relative_coordinates){
            cout << "SIDE_A: ";
            lambda(-point.second, point.first, SIDE_A);
            cout << "SIDE_B: ";
            lambda(point.second, -point.first, SIDE_B);
        }
        
    }

    template<typename Lambda>
    void traverse_both(Lambda lambda){
        cout << "Side A Special: ";
        lambda(0, 0, SIDE_A, NOT_ROTATED);
        cout << "Side B Special: ";
        lambda(0, 0, SIDE_A, ROTATED);

        for(Point point : this -> relative_coordinates){
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

    int get_side() const { return this -> side; }
    int get_area() const { return this -> area; }

    friend ostream& operator << (ostream& os, const MagicPoints& magic_points){
        os << "Magic Points: [";
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
        {0, 1},
        {1, 1}, {1, 0}, {1, -1},
        {2, 1}, {2, 0}, {2, -1},
        {3, 1}, {3, 0}, {3, -1},
        {4, 1}, {4, 0}, {4, -1},
        {5, 1}, {5, 0}, {5, -1}
    }, 
    11
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
    11
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
    11
);

MagicPoints window3(
    vector<Point>{
        {0, 1}, {-1, 1}, 
        {1, 1}, {1, 0},
        {2, 2}, {2, 1}, {2, 0},
        {3, 2}, {3, 1},
        {4, 3}, {4, 2}, {4, 1},
        {5, 4}, {5, 3}, {5, 2}
    },    
    11
);

MagicPoints window4(
    vector<Point>{
        {0, 1}, 
        {1, 1}, {1, 0}, {1, -1},
        {2, 2}, {2, 1}, {2, 0},
        {3, 3}, {3, 2}, {3, 1},
        {4, 4}, {4, 3}, {4, 2},
        {5, 5}, {5, 4}, {5, 3}
    },
    11
);

MagicPoints window5(
    vector<Point>{
        {0, 1},
        {1, 1}, {1, 0}, {1, 2}, 
        {2, 3}, {2, 2}, {2, 1},
        {3, 4}, {3, 3}, {3, 2},
        {4, 5}, {4, 4}, {4, 3},
        {5, 5}, {5, 4}
    },
    11
);

MagicPoints window6(
    vector<Point>{
        {0, 1},
        {1, 3}, {1, 2}, {1, 1}, {1, 0},
        {2, 4}, {2, 3}, {2, 2}, {2, 1}, {2, 0},
        {3, 5}, {3, 4}, {3, 3}, {3, 2}, {3, 1},
        {4, 5}, {4, 4},
        {5, 5}
    },
    11
);

MagicPoints window7(
    vector<Point>{
        {0, 1},
        {1, 4}, {1, 3}, {1, 2}, {1, 1}, {1, 0},
        {2, 5}, {2, 4}, {2, 3}, {2, 2}, {2, 1}, {2, 0},
        {3, 5}, {3, 4},
        {4, 5}
    }, 
    11
);

MagicPoints window8(
    vector<Point>{
        {0, 4}, {0, 3}, {0, 2}, {0, 1},
        {1, 5}, {1, 4}, {1, 3}, {1, 2}, {1, 1}, {1, 0},
        {2, 5}, {2, 4}, {2, 3},
        {3, 5}
    },
    11
);


MagicPoints window9(
    vector<Point>{
        {0, 5}, {0, 4}, {0, 3}, {0, 2}, {0, 1},
        {1, 5}, {1, 4}, {1, 3}, {1, 2}, {1, 1}, {1, 0}, {1, -1}, 
        {2, 5}, {2, 4}, {2, 3}
    },
    11
);


vector<MagicPoints> all_windows = { window0, window1, window2, window3, window4, window5, window6, window7, window8, window9 };