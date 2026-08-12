#pragma once
#include "benchmark/benchmark.h"
#include "utility"
#include "../../lib/filter.hpp"
#include "mean_baseline.hpp"

#include "random"

using namespace std;
using namespace benchmark;

class WindowSetupFixture : public Fixture {
  public:
    Mat data;
    unsigned int seed = 0;
    double res;
    void SetUp(State& state) override {
      random_device rd;
      //seed = rd();
      mt19937 gen(seed);
      uniform_real_distribution<double> distribution(0, 1);
      array<double, 11 * 11> arr;
      
      generate(arr.begin(), arr.end(), [&]{
	return  distribution(gen); 
      });

      Mat arr_mat(arr, false);
      data = arr_mat.reshape(0, 11);
    } 
};


BENCHMARK_F(WindowSetupFixture, w0_opt)(State& state){
  for(auto _ : state){
    res = calc_mean_complex<double>(data, 5, 5, get<0>(all_windows), NOT_ROTATED);
    DoNotOptimize(res);
  }
  state.SetLabel(to_string(res) + " With seed: " + to_string(seed));
};


constinit BitSetMask<11> base_window0(w0_arr);


BENCHMARK_F(WindowSetupFixture, w0_base)(State& state){
  for(auto _ : state){
    res = calc_mean_complex<double, 11>(data, 5, 5, base_window0, NOT_ROTATED);
    DoNotOptimize(res);
  }
  state.SetLabel(to_string(res) + " With seed: " + to_string(seed));
};

BENCHMARK_F(WindowSetupFixture, w1_opt)(State& state){
  for(auto _ : state){
    res = calc_mean_complex<double>(data, 5, 5, get<1>(all_windows), NOT_ROTATED);
    DoNotOptimize(res);
  }
  state.SetLabel(to_string(res) + " With seed: " + to_string(seed));
};


constinit BitSetMask<11> base_window1(w1_arr);
BENCHMARK_F(WindowSetupFixture, w1_base)(State& state){
  for(auto _ : state){
    res = calc_mean_complex<double, 11>(data, 5, 5, base_window1, NOT_ROTATED);
    DoNotOptimize(res);
  }
  state.SetLabel(to_string(res) + " With seed: " + to_string(seed));
};

/* Baseline */

BENCHMARK_F(WindowSetupFixture, w10_opt)(State& state){
  for(auto _ : state){
    res = calc_mean_complex<double>(data, 5, 5, get<0>(all_windows), ROTATED);
    DoNotOptimize(res);
  }
  state.SetLabel(to_string(res) + " With seed: " + to_string(seed));
};



BENCHMARK_F(WindowSetupFixture, w10_base)(State& state){
  for(auto _ : state){
    res = calc_mean_complex<double, 11>(data, 5, 5, base_window0, ROTATED);
    DoNotOptimize(res);
  }
  state.SetLabel(to_string(res) + " With seed: " + to_string(seed));
};
