
#include "bitset"
#include "point.hpp"

using namespace std;
using namespace Magic;

/* Apply fold method on the Mask later */
template<uint Len>
class BitSetMask {
    private:
        bitset<Len * Len> mask;


    public:

        template<size_t N, size_t M>
        static constexpr bitset<Len * Len> init(const array<Point, N>& points, const array<Point, M>& bit_mask){
            bitset<Len * Len> premask;
            premask.set();

            int center = Len / 2;

            //right sector
            //for(auto [x, y] : points)
            //   premask[((center - y) * Len) + (center + x)] = true;
            

            // left
            //for(auto [x, y] : points)
            //    premask[((center + y) * Len) + (center - x)] = true;

            for(auto [x, y] : bit_mask)
                premask[((center - y) * Len) + (center + x)] = false;

            for(auto [x, y] : bit_mask)
                premask[((center + y) * Len) + (center - x)] = false;
            
            premask[(center * Len) + center] = false;

            return premask;
        }

        template<size_t N, size_t M>
        constexpr BitSetMask(const array<Point, N>& points, const array<Point, M>& bit_mask) : mask(init(points, bit_mask)) {}

        size_t size() const noexcept { return Len * Len; }
        size_t size_x() const noexcept { return Len; } 
        size_t size_y() const noexcept { return Len; } 

        bool flip(uint x, uint y) const {
            this -> mask[(x * Len) + y] = !this -> mask[(x * Len) + y];

            return this -> mask[(x * Len) + y];
        }

        bool operator () (uint x, uint y) const {
            return mask[(y * Len) + x];
        }

        friend ostream& operator << (ostream& os, const BitSetMask& bitset_2d){
            os << "Bit Set 2D: [" << endl;

            os << "N:  ";
            for(int i = 0; i < Len; i++)
                os << i << " ";

            os << endl << "----";

            for(int i = 0; i < Len; i++)
                os << "--";

            os << endl;

            for(int i = 0; i < Len; i++){
                if(i < 10)
                    os << i << " | ";
                else
                    os << i << "| ";

                for(int j = 0; j < Len; j++)
                    os << bitset_2d.mask[(i * Len) + j] << " ";
                os << endl;
            }
            os << "]" << endl;

            os << "R:  ";
            for(int i = 0; i < Len; i++)
                os << i << " ";

            os << endl << "----";

            for(int i = 0; i < Len; i++)
                os << "--";

            os << endl;

            for(int j = 0; j < Len; j++){
                if(j < 10)
                    os << j << " | ";
                else
                    os << j << "| ";

                for(int i = 0; i < Len; i++)
                    os << bitset_2d.mask[(i * Len) + j] << " ";
                os << endl;
            }
            
            os << "]" << endl;
            return os;
        }
};