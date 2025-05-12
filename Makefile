
CXX := g++
CXXFLAGS := -std=c++17 -O3 -march=native -Wall -Wextra -I/usr/include/eigen3
EIGEN_INCLUDE := /usr/include/eigen3

SRC_DIR := .
INCLUDE_DIR := .
TESTS_DIR := .

TARGETS := gauss_solver generate_system gauss_tests

all: $(TARGETS)

gauss_solver: main.cpp csv_utils.cpp gauss.cpp random_generator.cpp
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -I$(EIGEN_INCLUDE) $^ -o $@

generate_system: large_gen.cpp csv_utils.cpp random_generator.cpp
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -I$(EIGEN_INCLUDE) $^ -o $@

gauss_tests: test.cpp csv_utils.cpp gauss.cpp random_generator.cpp
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -I$(EIGEN_INCLUDE) $^ -lgtest -lgtest_main -lpthread -o $@

test: gauss_tests
	./gauss_tests

gen_test: generate_system
	./generate_system 10 test_system.csv
	@echo "Тестовая система 10x10 создана в test_system.csv"

clean:
	rm -f $(TARGETS) *.o *.csv

.PHONY: all test clean gen_test
