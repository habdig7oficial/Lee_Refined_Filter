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

- use binary search instead of linear search
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




# Unused snippets

constexpr array w8_arr = {
        Point{0, 4}, Point{0, 3}, Point{0, 2}, Point{0, 1},
        Point{1, 5}, Point{1, 4}, Point{1, 3}, Point{1, 2}, Point{1, 1}, Point{1, 0},
        Point{2, 5}, Point{2, 4}, Point{2, 3},
        Point{3, 5}
};
auto window8 = magic_points_factory<w8_arr, DIMENSION, 8>();

constexpr array w9_arr = {
        Point{0, 5}, Point{0, 4}, Point{0, 3}, Point{0, 2}, Point{0, 1},
        Point{1, 5}, Point{1, 4}, Point{1, 3}, Point{1, 2}, Point{1, 1}, Point{1, 0}, Point{1, -1}, 
        Point{2, 5}, Point{2, 4}, Point{2, 3}
};
auto window9 = magic_points_factory<w9_arr, DIMENSION, 9>();