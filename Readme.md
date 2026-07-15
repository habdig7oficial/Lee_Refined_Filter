# Run with:
```
make compile && ./exec.elf --image img/Simulated/phi_raster_noisy.tif --coherence img/Simulated/map_coherence_gierull.tif
```


```
2 * (l - 1)
```




```
Para se calcular quais pontos azuis devem ser considerados, basta calcular metade e transpor x,y uma vez que eles sao espelhos.

x,y -> -x,-y
x,y -> y,x
As imagens totais podens ser transpostas tambem 0 e 10 pi sao iguais

isso pode ser utizado tambem para economizar memoria, o importante é sabe o x,y dos pontos azuis

8 pi / 20 esta errado ele deve ser simetrico em cima e embaixo com 2 e 2
```