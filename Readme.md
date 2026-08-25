# Run with:
```
make compile && ./exec.elf --image img/Simulated/phi_raster_noisy.tif --coherence img/Simulated/map_coherence_gierull.tif
```

# Run with:
```
make release && time ./prod_binary --image img/Simulated/phi_raster_noisy.tif --coherence img/Simulated/map_coherence_gierull.tif
```



```
2 * (n - 1)
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


## Road map 

See calc_mean_complex optimization acording to paper formula
add select window integrated test

# Unused 

Copyright © 2026 Terry Jones Mateus Felipe da Silveira Vieira, Rogério de Oliveira, Anderson Adaime de Borba

This file is part of Geschwindigkeit.

Geschwindigkeit is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

Geschwindigkeit is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License along with Foobar. If not, see <https://www.gnu.org/licenses/>. 



  for(int i = 0; i < hello.end(); i++){
    cout << hello[i] << endl;
  }




    template<size_t Dim = dimension>
    static constexpr BitSetMask<Dim> gen_mask(double angle, double threshold){
        BitSetMask<Dim> mask {};

            #if CONSTEXP_SUPPORT == 1
                double s = sin(angle);
                double c = cos(angle);
            #else
                double s = gcem::sin(angle);
                double c = gcem::cos(angle);
            #endif

            int center = Dim / 2;
            for(int y = -center; y <= center; y++){
                double yc = y * c;
                for(int x = -center; x <= center; x++){
                    double xs = x * s;


                    #if CONSTEXP_SUPPORT == 1
                        double res = abs(xs - yc);
                    #else
                        double res = gcem::abs(xs - yc);
                    #endif

                    if(res <= threshold / 2){
                        /* Side A  NOT_ROTATED*/
                        mask[center - x, center + y] = true;
                        //mask[center + y, center - x] = true;
                        //mask.push_back(Point{x, y});
                    }
                }
            }

        return mask;
    }