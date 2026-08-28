#pragma once
#include "benchmark/benchmark.h"
#include "utility"
#include "../../lib/filter.hpp"
#include "mean_baseline.hpp"
#include "../magic_points_hardcoded.hpp"

#include "random"


using namespace std;
using namespace benchmark;

class WindowSetupFixture : public Fixture {
  public:
    Mat data;
    inline static unsigned int seed = 0; /* Same Seed (Variable must be inline) */
    double res;
    void SetUp(State& state) override {
      random_device rd;
      if(seed == 0)
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

};

/* Fix this code repetition later */

constinit array<BitSetMask<11>, 10> base_windows = { BitSetMask<11>(w0_arr), BitSetMask<11>(w1_arr), BitSetMask<11>(w2_arr), BitSetMask<11>(w3_arr), BitSetMask<11>(w4_arr), BitSetMask<11>(w5_arr), BitSetMask<11>(w6_arr), BitSetMask<11>(w7_arr), BitSetMask<11>(w8_arr), BitSetMask<11>(w9_arr) };


#define BENCHMARK_MEAN_COMPLEX(index, window_name, rotation) \
BENCHMARK_F(WindowSetupFixture, rotation##_##window_name##_##index)(State& state){ \
  for(auto _ : state){ \
    res = calc_mean_complex(data, 5, 5, get<index>(window_name), rotation); \
    DoNotOptimize(res); \
    ClobberMemory(); \
  } \
  state.SetLabel(#window_name);  \
  state.counters["index"] = index; \
  state.counters["rotation"] = rotation; \
  state.counters["seed"] = (double)seed; \
  state.counters["res"] = (double)res; \
};

//state.SetLabel(to_string(res) + " With seed: " + to_string(seed)); \

/* Fix this part latter */
/* NOT_ROTATED windows */
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


/* Rotated Windows */


BENCHMARK_MEAN_COMPLEX(0, all_windows, ROTATED);
BENCHMARK_MEAN_COMPLEX(0, base_windows, ROTATED);

BENCHMARK_MEAN_COMPLEX(1, all_windows, ROTATED);
BENCHMARK_MEAN_COMPLEX(1, base_windows, ROTATED);

BENCHMARK_MEAN_COMPLEX(2, all_windows, ROTATED);
BENCHMARK_MEAN_COMPLEX(2, base_windows, ROTATED);

BENCHMARK_MEAN_COMPLEX(3, all_windows, ROTATED);
BENCHMARK_MEAN_COMPLEX(3, base_windows, ROTATED);

BENCHMARK_MEAN_COMPLEX(4, all_windows, ROTATED);
BENCHMARK_MEAN_COMPLEX(4, base_windows, ROTATED);

BENCHMARK_MEAN_COMPLEX(5, all_windows, ROTATED);
BENCHMARK_MEAN_COMPLEX(5, base_windows, ROTATED);

BENCHMARK_MEAN_COMPLEX(7, all_windows, ROTATED);
BENCHMARK_MEAN_COMPLEX(7, base_windows, ROTATED);

BENCHMARK_MEAN_COMPLEX(8, all_windows, ROTATED);
BENCHMARK_MEAN_COMPLEX(8, base_windows, ROTATED);

BENCHMARK_MEAN_COMPLEX(9, all_windows, ROTATED);
BENCHMARK_MEAN_COMPLEX(9, base_windows, ROTATED);
