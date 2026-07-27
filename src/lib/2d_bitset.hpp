
#include "bitset"
#include "point.hpp"

using namespace std;

template<uint LenX, uint LenY>
class BitSet2D {
    private:
        bitset<LenX * LenY> mask;


    public:

        template<size_t N>
        constexpr BitSet2D(const array<Magic::Point, N>& points){
            //cout << "BIT MASK HELLO";
        }

        size_t size() const noexcept { return LenX * LenY; }
        size_t size_x() const noexcept { return LenX; } 
        size_t size_y() const noexcept { return LenY; } 

        bool flip(uint x, uint y) const {
            this -> mask[(x * LenY) + y] = !this -> mask[(x * LenY) + y];

            return this -> mask[(x * LenY) + y];
        }

        bool operator () (uint x, uint y) const {
            return mask[(x * LenY) + y];
        }

        friend ostream& operator << (ostream& os, const BitSet2D& bitset_2d){
            os << "Bit Set 2D: [";

            os << "]" << endl;
        return os;
    }
};