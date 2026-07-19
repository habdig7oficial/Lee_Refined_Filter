# Run with:
```
make compile && ./exec.elf --image img/Simulated/phi_raster_noisy.tif --coherence img/Simulated/map_coherence_gierull.tif
```

# Run with:
```
make release && ./prod_binary --image img/Simulated/phi_raster_noisy.tif --coherence img/Simulated/map_coherence_gierull.tif
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

use binary search instead of linear search
use fold method to pass across less points
Replaced calc min complex with AI sin,cos method


## Indentified errors

The 8th window in the article was wrong, it should mirror the 18th window, 1 pixel left 
The 18th window in the article is assymetric

The 17th window in the article was wrong, it should mirror the 17th window, solution add one pixel

The 2th window in the code was also wrong, it should be one square in y lower.