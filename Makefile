# OpenCv and Gnu Scientific Library (gsl) must be installed

CXX_FLAGS = `pkg-config --cflags --libs opencv4 gsl`
compile:
	 g++ src/main.cpp -o exec.elf $(CXX_FLAGS) 

run: compile
	./exec.elf
