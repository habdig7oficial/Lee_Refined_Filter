CXX_FLAGS = `pkg-config --cflags --libs opencv4`
compile:
	 g++ src/main.cpp -o exec.elf $(CXX_FLAGS) 

run: compile
	./exec.elf
