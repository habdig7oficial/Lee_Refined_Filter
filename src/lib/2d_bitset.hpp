
#include "bitset"
#include "point.hpp"

using namespace std;
using namespace Magic;

/* Apply fold method on the Mask later */
template<uint Len>
class BitSetMask {
    private:
        static constexpr size_t MaskSize = (Len + Len % 2) * (Len + Len % 2) + (Len + Len % 2);
        bitset<MaskSize> mask;


    public:

        template<size_t N, size_t M>
        static constexpr bitset<MaskSize> init(const array<Point, N>& points, const array<Point, M>& bit_mask){
            bitset<MaskSize> premask;
            premask.set();

            int center = Len / 2;

            // NOT_ROTATED
            // SIDE A 
            for(auto [x, y] : bit_mask)
                premask[((center - y) * Len) + (center + x)] = false;
            
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

        static void print_helper(ostream& os, const BitSetMask& bitset_2d, bool is_rotated){
            os << "Bit Set 2D: [" << endl;

            os << ((is_rotated == NOT_ROTATED) ? "N:  " : "R:  ");
            for(int i = 0; i < Len; i++)
                os << i << " ";

            os << endl << "----";
            for(int i = 0; i < Len; i++)
                os << "--";

            os << endl;

            int begin, end;
            if(is_rotated == NOT_ROTATED){
                begin = Len / 2 + Len % 2;
                end = 0;
            }
            else {
                begin = 0;
                end = Len / 2 + Len % 2;
            }


            for(int i = begin; (is_rotated == NOT_ROTATED) ? i > end : i < end; (is_rotated == NOT_ROTATED) ? i-- : i++){
                os << i << ((abs(i) < 10) ? " | " : "| ");



                os << endl;
            }

            os << "]" << endl;
        }

        friend ostream& operator << (ostream& os, const BitSetMask& bitset_2d){
            print_helper(os, bitset_2d, NOT_ROTATED);
            print_helper(os, bitset_2d, ROTATED);
            return os;
        }
};