
#include "bitset"
#include "point.hpp"

using namespace std;
using namespace Magic;

/* Apply fold method on the Mask later */
template<uint Len>
class BitSetMask {
    private:

        static constexpr uint Size = Len * Len;
        bitset<Size> mask;


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
                premask[((center - y) * Len) + x] = true;

            return premask;
        }

        template<size_t N, size_t M>
        constexpr BitSetMask(const array<Point, N>& points, const array<Point, M>& bit_mask) : mask(init(points, bit_mask)) {}

        template<size_t M>
        static constexpr bitset<Len * Len> init(const array<Point, M>& bit_mask){
            bitset<Len * Len> premask;
            premask.set();

            int center = Len / 2;

            for(auto [x, y] : bit_mask)
                premask[((center - y) * Len) + (center + x)] = false;

            for(auto [x, y] : bit_mask)
                premask[((center + y) * Len) + (center - x)] = false;
            
            premask[(center * Len) + center] = false;

            return premask;
        }
  
        template<size_t M>
        constexpr BitSetMask(const array<Point, M>& bit_mask) : mask(init(bit_mask)) {}
  
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

        static void print_helper (ostream& os, const BitSetMask& bitset_2d, bool mirror){
            constexpr uint side = (Len + 1) / 2;
            os << Size << ") Bit Set 2D: [" << endl;

            if(mirror)
                os << "R:  ";
            else 
                os << "N:  ";

            for(int i = Len / 2; i < Len; i++)
                os << i << " ";

            os << endl << "----";

            for(int i = 0; i < (Len + 1) / 2; i++)
                os << "--";

            os << endl;


            if(!mirror){
                for(int i = 0; i < Len; i++){
                    if(i < 10)
                        os << i << " | ";
                    else
                        os << i << "| ";

                    for(int j = 0; j < side; j++)
                        os << bitset_2d.mask[(i * side) + j] << " "; // 

                    os << endl;
                }
            }
            else {
                for(int i = 0; i < side; i++){
                    if(i < 10)
                        os << i << " | ";
                    else
                        os << i << "| ";

                    for(int j = 0; j < Len; j++)
                        os << bitset_2d.mask[(j * side) + i] << " "; // bitset_2d.mask[(j * side) + i]

                    os << endl;
                }
            }

            os << "]" << endl;

        }

        friend ostream& operator << (ostream& os, const BitSetMask& bitset_2d){
            print_helper(os, bitset_2d, false);
            print_helper(os, bitset_2d, true);
 
            return os;
        }
};
