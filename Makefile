CXX = g++
CXXFLAGS = -std=c++17 -O3 -march=native -Wall -Wextra -I/usr/include/eigen3

SRC = main.cpp csv_utils.cpp gauss.cpp random_generator.cpp large_gen.cpp

all: bin/gauss_app

bin/gauss_app: $(SRC)
	@mkdir -p bin
	$(CXX) $(CXXFLAGS) $^ -o $@

clean:
	rm -rf bin/*

.PHONY: all clean
