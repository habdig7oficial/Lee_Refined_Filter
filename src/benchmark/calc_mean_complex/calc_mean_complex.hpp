#pragma once
#include "benchmark/benchmark.h"

using namespace std;
using namespace benchmark;

static void bm_calc_mean_complex(State& state){
  for(auto _ : state)
    string empty;
}

BENCHMARK(bm_calc_mean_complex);
