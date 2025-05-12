CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I/usr/include/eigen3
GTEST_LIBS = -lgtest -lgtest_main -lpthread

all: bin/gauss_solver bin/generate_system bin/gauss_tests

bin/gauss_solver: main.cpp csv_utils.cpp gauss.cpp random_generator.cpp large_gen.cpp
	@mkdir -p bin
	$(CXX) $(CXXFLAGS) $^ -o $@

bin/generate_system: generate_entry.cpp large_gen.cpp csv_utils.cpp random_generator.cpp
	@mkdir -p bin
	$(CXX) $(CXXFLAGS) $^ -o $@

bin/gauss_tests: test.cpp csv_utils.cpp gauss.cpp random_generator.cpp
	@mkdir -p bin
	$(CXX) $(CXXFLAGS) $^ $(GTEST_LIBS) -o $@

test: bin/gauss_tests
	./bin/gauss_tests

clean:
	rm -rf bin/*

.PHONY: all test clean
