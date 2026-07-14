# OpenCv and Gnu Scientific Library (gsl) must be installed

CXX_FLAGS = `pkg-config --cflags --libs opencv4 gsl`


# R binds for test only
R_TEST    := $(shell Rscript -e "cat(R.home('include'))")
RCPP_TEST := $(shell Rscript -e "cat(system.file('include', package='Rcpp'))")
R_LIBS_TEST   := $(shell Rscript -e "cat(R.home('lib'))")

RINSIDE_CXX_TEST := $(shell Rscript -e "RInside:::CxxFlags()") 
RINSIDE_LDF_TEST := $(shell Rscript -e "RInside:::LdFlags()") 

CXX_FLAGS_TEST = `pkg-config --cflags --libs opencv4 gsl catch2` # Catch2 for tests

compile:
	 g++ -std=c++20 src/main.cpp -o exec.elf $(CXX_FLAGS) 

run: compile
	./exec.elf

test:
	g++ -std=c++20 src/tests/test.cpp -o test.elf -I"$(R_TEST)" -I"$(RCPP_TEST)" -L"$(R_LIBS_TEST)" $(RINSIDE_CXX_TEST) $(RINSIDE_LDF_TEST) -lR $(CXX_FLAGS_TEST) && ./test.elf "[first_pass]" #--rng-seed 3908993432
#leaks: compile
#	valgrind --leak-check=full --track-origins=yes -- ./exec.elf $(ARGS)
