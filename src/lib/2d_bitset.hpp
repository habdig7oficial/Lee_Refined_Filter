
#include "bitset"
#include "point.hpp"

using namespace std;
using namespace Magic;

template<uint LenX, uint LenY>
class BitSetMask {
    private:
        bitset<LenX * LenY> mask;


    public:

        template<size_t N>
        static constexpr bitset<LenX * LenY> init(const array<Point, N>& points){
            bitset<LenX * LenY> premask(1);


            return premask;
        }

        template<size_t N>
        constexpr BitSetMask(const array<Point, N>& points) : mask(init(points)) {}

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

        friend ostream& operator << (ostream& os, const BitSetMask& bitset_2d){
            os << "Bit Set 2D: [";

            os << "]" << endl;
        return os;
    }
};