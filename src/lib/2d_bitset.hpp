
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
            bitset<LenX * LenY> premask = {};

            int center_x = LenX / 2;
            int center_y = LenY / 2;

            for(auto [x, y] : points){
                premask.set(((center_y - y) * LenX) + (center_x + x));
            }

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
            os << "Bit Set 2D: [" << endl;

            os << "    ";
            for(int i = 0; i < LenX; i++)
                os << i << " ";

            os << endl;

            for(int i = 0; i < LenX; i++)
                os << "--";

            os << endl;

            for(int i = 0; i < LenX; i++){
                if(i < 10)
                    os << i << " | ";
                else
                    os << i << "| ";

                for(int j = 0; j < LenX; j++)
                    os << bitset_2d.mask[(i * LenY) + j] << " ";
                os << endl;
            }

            
            os << "]" << endl;
            return os;
        }
};