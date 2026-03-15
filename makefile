CXX = g++-14
CXXFLAGS = -O3 -std=c++23 -Wall -Iinclude -Isrc -MMD -MP

SRC = $(shell find src -name '*.cpp')
OBJ = $(SRC:src/%.cpp=build/%.o)
DEPS = $(OBJ:.o=.d)

LIB = build/libtriedb.a
CLI = build/triedb-cli
BEN = build/benchmark

all: $(LIB) $(CLI) $(BEN)

-include $(DEPS)

$(LIB): $(OBJ)
	mkdir -p build
	ar rcs $@ $^

build/%.o: src/%.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(CLI): tools/cli.cpp $(LIB)
	$(CXX) $(CXXFLAGS) $< -Lbuild -ltriedb -o $@

$(BEN): bench/benchmark.cpp $(LIB)
	$(CXX) $(CXXFLAGS) $< -Lbuild -ltriedb -o $@

clean:
	rm -rf build