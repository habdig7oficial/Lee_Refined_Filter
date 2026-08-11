#pragma once
#include "benchmark/benchmark.h"
#include "utility"
#include "../../lib/filter.hpp"

#include "random"

using namespace std;
using namespace benchmark;

class WindowSetupFixture : public Fixture {
  public:
    Mat data;
    unsigned int seed;
    double res;
    void SetUp(State& state) override {
      random_device rd;
      seed = rd();
      mt19937 gen(seed);
      uniform_real_distribution<double> distribution(0, 1);
      array<double, 11 * 11> arr;
      
      generate(arr.begin(), arr.end(), [&]{
	return  distribution(gen); 
      });

      Mat arr_mat(arr, false);
      data = arr_mat.reshape(0, 11);
    }

    template<size_t WinNum>
    void mean_complex_opt(State& state){
      
    }
  
};


BENCHMARK_F(WindowSetupFixture, mean_complex_opt)(State& state){
  for(auto _ : state){
    res = calc_mean_complex<double>(data, 5, 5, get<0>(all_windows), NOT_ROTATED);
    DoNotOptimize(res);
  }
  state.SetLabel(to_string(res) + " With seed: " + to_string(seed));
};

/*
template <size_t WinNum>
struct Register {
  Register(){
    BENCHMARK_REGISTER_F(WindowSetupFixture, mean_complex_opt<WinNum>);
  }
};


template <size_t ...Is>
void register_benchmark(index_sequence<Is ...>){
  (Register<Is>{}, ...);
}

const bool registred = [](){
  register_benchmark(make_index_sequence<20>{});
  
  return true;
}();
*/
/*

     benchmark::internal::RegisterBenchmarkInternal( new ::benchmark::internal::FixtureDeterminer<WindowSetupFixture>(
      "Hello",
      to_string(Is),
      &WindowSetupFixture::RunBenchmark<Is>
    ))
*/
