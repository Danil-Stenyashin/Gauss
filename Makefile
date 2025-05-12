CXX = g++
CXXFLAGS = -std=c++17 -O3 -march=native -Wall -Wextra -I/usr/include/eigen3
GTEST_LIBS = -lgtest -lgtest_main -lpthread

SRC = main.cpp csv_utils.cpp gauss.cpp random_generator.cpp
TEST_SRC = test.cpp

TARGETS = bin/gauss_app bin/gauss_tests

all: $(TARGETS)

bin/gauss_app: $(SRC)
	@mkdir -p bin
	$(CXX) $(CXXFLAGS) $^ -o $@

bin/gauss_tests: $(TEST_SRC) $(filter-out main.cpp, $(SRC))
	@mkdir -p bin
	$(CXX) $(CXXFLAGS) $^ $(GTEST_LIBS) -o $@

test: bin/gauss_tests
	./bin/gauss_tests

clean:
	rm -rf bin/*

.PHONY: all test clean
