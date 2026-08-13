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


## Road map 

See calc_mean_complex optimization acording to paper formula
add select window integrated test

# Unused 


BENCHMARK_F(WindowSetupFixture, w0_base)(State& state){
  for(auto _ : state){
    res = calc_mean_complex<double, 11>(data, 5, 5, base_window0, NOT_ROTATED);
    DoNotOptimize(res);
    ClobberMemory();
  }
  state.SetLabel(to_string(res) + " With seed: " + to_string(seed));
};

BENCHMARK_F(WindowSetupFixture, w1_opt)(State& state){
  for(auto _ : state){
    res = calc_mean_complex<double>(data, 5, 5, get<1>(all_windows), NOT_ROTATED);
    DoNotOptimize(res);
    ClobberMemory();
  }
  state.SetLabel(to_string(res) + " With seed: " + to_string(seed));
};


constinit BitSetMask<11> base_window1(w1_arr);
BENCHMARK_F(WindowSetupFixture, w1_base)(State& state){
  for(auto _ : state){
    res = calc_mean_complex<double, 11>(data, 5, 5, base_window1, NOT_ROTATED);
    DoNotOptimize(res);
    ClobberMemory();
  }
  state.SetLabel(to_string(res) + " With seed: " + to_string(seed));
};

/* Baseline */

BENCHMARK_F(WindowSetupFixture, w10_opt)(State& state){
  for(auto _ : state){
    res = calc_mean_complex<double>(data, 5, 5, get<0>(all_windows), ROTATED);
    DoNotOptimize(res);
    ClobberMemory();
  }
  state.SetLabel(to_string(res) + " With seed: " + to_string(seed));
};



BENCHMARK_F(WindowSetupFixture, w10_base)(State& state){
  for(auto _ : state){
    res = calc_mean_complex<double, 11>(data, 5, 5, base_window0, ROTATED);
    DoNotOptimize(res);
    ClobberMemory();
  }
  state.SetLabel(to_string(res) + " With seed: " + to_string(seed));
};





BENCHMARK_MEAN_COMPLEX(0, all_windows, NOT_ROTATED);
BENCHMARK_MEAN_COMPLEX(0, base_windows, NOT_ROTATED);

BENCHMARK_MEAN_COMPLEX(1, all_windows, NOT_ROTATED);
BENCHMARK_MEAN_COMPLEX(1, base_windows, NOT_ROTATED);

BENCHMARK_MEAN_COMPLEX(2, all_windows, NOT_ROTATED);
BENCHMARK_MEAN_COMPLEX(2, base_windows, NOT_ROTATED);

BENCHMARK_MEAN_COMPLEX(3, all_windows, NOT_ROTATED);
BENCHMARK_MEAN_COMPLEX(3, base_windows, NOT_ROTATED);

BENCHMARK_MEAN_COMPLEX(4, all_windows, NOT_ROTATED);
BENCHMARK_MEAN_COMPLEX(4, base_windows, NOT_ROTATED);

BENCHMARK_MEAN_COMPLEX(5, all_windows, NOT_ROTATED);
BENCHMARK_MEAN_COMPLEX(5, base_windows, NOT_ROTATED);

BENCHMARK_MEAN_COMPLEX(7, all_windows, NOT_ROTATED);
BENCHMARK_MEAN_COMPLEX(7, base_windows, NOT_ROTATED);

BENCHMARK_MEAN_COMPLEX(8, all_windows, NOT_ROTATED);
BENCHMARK_MEAN_COMPLEX(8, base_windows, NOT_ROTATED);

BENCHMARK_MEAN_COMPLEX(9, all_windows, NOT_ROTATED);
BENCHMARK_MEAN_COMPLEX(9, base_windows, NOT_ROTATED);




let aggrated : Type[] = Array.from({length: benchmark.benchmarks.length }, ()=> ({}) as Type)

for (const element of benchmark.benchmarks) {
  aggrated[element.family_index][element.aggregate_name as keyof Type] = element as BenchmarkData
  console.log(`${element.family_index} - ${element.aggregate_name} ${aggrated[element.family_index][element.aggregate_name as keyof Type]?.name} - ${aggrated[element.family_index][element.aggregate_name as keyof Type]?.real_time}`);
  
}


    // Draw the bars using x and y properties from your data
    Plot.barY(aggrated, Plot.stackY({ x: (m:Type)=>m.median?.run_name.split("_").at(-1), y: (m:Type)=>m.median?.real_time, fill: "steelblue" })),
    