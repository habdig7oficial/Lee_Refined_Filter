# OpenCv and Gnu Scientific Library (gsl) must be installed

CXX = g++
CXX_FLAGS = `pkg-config --cflags --libs opencv4 gsl`

# Should be at least 23 because of constexpr bitset
CXX_VERSION=23


# R binds for test only
R_TEST    := $(shell Rscript -e "cat(R.home('include'))")
RCPP_TEST := $(shell Rscript -e "cat(system.file('include', package='Rcpp'))")
R_LIBS_TEST   := $(shell Rscript -e "cat(R.home('lib'))")

RINSIDE_CXX_TEST := $(shell Rscript -e "RInside:::CxxFlags()") 
RINSIDE_LDF_TEST := $(shell Rscript -e "RInside:::LdFlags()") 

CXX_FLAGS_TEST = `pkg-config --cflags --libs opencv4 gsl catch2` # Catch2 for tests
CXX_FLAGS_BENCHMARK = `pkg-config --cflags --libs opencv4 gsl benchmark` # Catch2 for tests


compile:
	 $(CXX) -march=native -fconstexpr-depth=4096 -std=c++$(CXX_VERSION) src/main.cpp -o exec.elf $(CXX_FLAGS)

release: 
	$(CXX) -march=native -fconstexpr-depth=4096 -O3 -std=c++$(CXX_VERSION) -DNDEBUG src/main.cpp -o prod_binary $(CXX_FLAGS) 

run: compile
	./exec.elf

testO0:
	$(CXX) -std=c++$(CXX_VERSION) -fconstexpr-depth=4096 -O0 -march=native src/tests/test.cpp -o test.elf -I"$(R_TEST)" -I"$(RCPP_TEST)" -L"$(R_LIBS_TEST)" $(RINSIDE_CXX_TEST) $(RINSIDE_LDF_TEST) -lR $(CXX_FLAGS_TEST) && ./test.elf --abort #--rng-seed 3144853315

testO3:
	$(CXX) -std=c++$(CXX_VERSION) -fconstexpr-depth=4096 -O3 -march=native src/tests/test.cpp -o test_optimized.elf -I"$(R_TEST)" -I"$(RCPP_TEST)" -L"$(R_LIBS_TEST)" $(RINSIDE_CXX_TEST) $(RINSIDE_LDF_TEST) -lR $(CXX_FLAGS_TEST) && ./test_optimized.elf --abort

test: testO0 testO3



benchmark:
	$(CXX) -std=c++$(CXX_VERSION) -fconstexpr-steps=0 -O3 -march=native -DNDEBUG src/benchmark/benchmark.cpp -o benchmark.elf $(CXX_FLAGS_BENCHMARK) && ./benchmark.elf --benchmark_repetitions=2 --benchmark_report_aggregates_only=true --benchmark_out=benchmark.json --benchmark_out_format=json

benchmark_paper:
	$(CXX) -std=c++$(CXX_VERSION) -fconstexpr-steps=0 -O3 -march=native -DNDEBUG src/benchmark/benchmark.cpp -o benchmark.elf $(CXX_FLAGS_BENCHMARK) && ./benchmark.elf --benchmark_min_warmup_time=2 --benchmark_repetitions=40 --benchmark_report_aggregates_only=true --benchmark_out=benchmark.json --benchmark_out_format=json


# Deno && Image magick required
benchmark_gen_graphics:
	deno run --allow-write src/benchmark/graphics.ts src/benchmark/grafics.ts && magick bar_chart.svg bar_chart.png

version: 
	$(CXX) --version

clean_bin:
	rm -f exec.elf test.elf test_optimized.elf prod_binary benchmark.elf

clean_img:
	rm -f gierull_plot.png magic_point.png magic_point2.png bar_chart.svg bar_chart.png

clean: clean_bin clean_img
#leaks: compile
#	valgrind --leak-check=full --track-origins=yes -- ./exec.elf $(ARGS)
