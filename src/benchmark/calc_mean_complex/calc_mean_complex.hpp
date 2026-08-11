#pragma once
#include "benchmark/benchmark.h"
#include "../../lib/filter.hpp"

#include "random"

using namespace std;
using namespace benchmark;

class WindowSetupFixture : public Fixture{
  public:
    double res;
    void SetUp(const State& state) override {
      random_device rd;
      mt19937 gen(rd());
      uniform_real_distribution<double> distribution(0, 1);
      array<double, 11 * 11> arr;

      
      
      generate(arr.begin(), arr.end(), [&]{
	return  distribution(gen); 
      });

      
    }
};


BENCHMARK_F(WindowSetupFixture, mean_complex_opt)(State& state){
  for(auto _ : state){
    res = 1;
    DoNotOptimize(res);
  }
  state.SetLabel(to_string(res));
};
