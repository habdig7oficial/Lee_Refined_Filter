# Run with:
```
make compile && ./exec.elf --image img/Simulated/phi_raster_noisy.tif --coherence img/Simulated/map_coherence_gierull.tif
```

# Run with:
```
make release && time ./prod_binary --image img/Simulated/phi_raster_noisy.tif --coherence img/Simulated/map_coherence_gierull.tif
```



```
2 * (l - 1)
```




```
x,y -> x,y & -x,-y 
Para se calcular quais pontos azuis devem ser considerados, basta calcular metade e transpor x,y uma vez que eles sao espelhos.

x,y -> y,x & -y, -x 
As imagens totais podens ser transpostas tambem 0 e 10 pi sao iguais

isso pode ser utizado tambem para economizar memoria, o importante é saber o x,y dos pontos azuis

8 pi / 20 esta errado ele deve ser simetrico em cima e embaixo com 2 e 2
```

## Major changes

- use binary search instead of linear search (I think it can be also a constexpr)
- use fold method to pass across less points
- Replaced calc min complex with AI sin,cos method
- Discoverd in line 362 all the math is useless it rechoose the same window
```
if(max(Mod(averages))<eth){ # region is plain 
```
perhaps when this if triggers it's better make the tradicional lee filter (see removed thrash commit)


*Notes:* On the relevant points some points in the vertices are wrong but they dont change the result, only the performance

Change the vector into a static array

## Indentified errors

The 8th window in the article was wrong, it should mirror the 18th window, 1 pixel left 
The 18th window in the article is assymetric

The 17th window in the article was wrong, it should mirror the 17th window, solution add one pixel

The 2th window in the code was also wrong, it should be one square in y lower.


# Unused 




            for(auto [x, y] : bit_mask)
                premask[((center + y) * Len) + (center - x)] = false;





            //right sector
            for(auto [x, y] : points)
                premask[((center - y) * Len) + (center + x)] = true;
            

            // left
            for(auto [x, y] : points)
                premask[((center + y) * Len) + (center - x)] = true;

            
            for(auto [x, y] : bit_mask)
                premask[((center - y) * Len) + (center + x)] = false;

            for(auto [x, y] : bit_mask)
                premask[((center + y) * Len) + (center - x)] = false;

            
            // zero
            premask[(center * Len) + center] = false;
            








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
mask(BitSetMask<DIMENSION, DIMENSION>(diff<M, N>(gen_static<N, M>(rl, side), rl))) 



       for(signed char point_y = y - INNER_HALF; point_y <= point_y + INNER_HALF; point_y++){
          for(signed char point_x = x - INNER_HALF; point_x <= point_x + INNER_HALF; point_x++){
            cout << "Point: (" << (int)point_x << ", " << (int)point_y << ") Real: (" << (int)x << ", " << (int)y << ") " << endl;
          }
        }
