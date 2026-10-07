CXX      := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -O2 -Iinclude
LIB_SRC  := $(filter-out src/main.cpp, $(wildcard src/*.cpp))
LIB_OBJ  := $(LIB_SRC:src/%.cpp=build/%.o)

all: build/chronosync build/tests build/benchmark

build/%.o: src/%.cpp | build
	$(CXX) $(CXXFLAGS) -c $< -o $@

build/chronosync: $(LIB_OBJ) src/main.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

build/tests: $(LIB_OBJ) tests/test_main.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

build/benchmark: $(LIB_OBJ) benchmark/benchmark.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

build:
	mkdir -p build

run: build/chronosync
	./build/chronosync
test: build/tests
	./build/tests
bench: build/benchmark
	./build/benchmark
clean:
	rm -rf build

.PHONY: all run test bench clean
