# OpenCv and Gnu Scientific Library (gsl) must be installed

CXX = clang++
CXX_FLAGS = `pkg-config --cflags --libs opencv4 gsl`


# R binds for test only
R_TEST    := $(shell Rscript -e "cat(R.home('include'))")
RCPP_TEST := $(shell Rscript -e "cat(system.file('include', package='Rcpp'))")
R_LIBS_TEST   := $(shell Rscript -e "cat(R.home('lib'))")

RINSIDE_CXX_TEST := $(shell Rscript -e "RInside:::CxxFlags()") 
RINSIDE_LDF_TEST := $(shell Rscript -e "RInside:::LdFlags()") 

CXX_FLAGS_TEST = `pkg-config --cflags --libs opencv4 gsl catch2` # Catch2 for tests
CXX_FLAGS_BENCHMARK = `pkg-config --cflags --libs opencv4 gsl benchmark` # Catch2 for tests


compile:
	 $(CXX) -march=native -fconstexpr-steps=0 -std=c++23 src/main.cpp -o exec.elf $(CXX_FLAGS) 

release: 
	$(CXX) -march=native -fconstexpr-steps=0 -O3 -std=c++23 -DNDEBUG src/main.cpp -o prod_binary $(CXX_FLAGS) 

run: compile
	./exec.elf

testO0:
	$(CXX) -std=c++23 -fconstexpr-steps=0 -O0 -march=native src/tests/test.cpp -o test.elf -I"$(R_TEST)" -I"$(RCPP_TEST)" -L"$(R_LIBS_TEST)" $(RINSIDE_CXX_TEST) $(RINSIDE_LDF_TEST) -lR $(CXX_FLAGS_TEST) && ./test.elf --abort #--rng-seed 3144853315

testO3:
	$(CXX) -std=c++23 -fconstexpr-steps=0 -O3 -march=native src/tests/test.cpp -o test_optimized.elf -I"$(R_TEST)" -I"$(RCPP_TEST)" -L"$(R_LIBS_TEST)" $(RINSIDE_CXX_TEST) $(RINSIDE_LDF_TEST) -lR $(CXX_FLAGS_TEST) && ./test_optimized.elf

test: testO0 testO3



benchmark:
	$(CXX) -std=c++23 -fconstexpr-steps=0 -O3 -march=native -DNDEBUG src/benchmark/benchmark.cpp -o benchmark.elf $(CXX_FLAGS_BENCHMARK) && ./benchmark.elf 

version: 
	$(CXX) --version

clean:
	rm exec.elf test.elf test_optimized.elf prod_binary
#leaks: compile
#	valgrind --leak-check=full --track-origins=yes -- ./exec.elf $(ARGS)
