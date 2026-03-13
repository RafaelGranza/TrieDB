CXX = g++
CXXFLAGS = -O3 -std=c++20 -Wall -Iinclude -Isrc

SRC = $(shell find src -name '*.cpp')

OBJ = $(SRC:src/%.cpp=build/%.o)

LIB = build/libtriedb.a
CLI = build/triedb-cli

all: $(LIB) $(CLI)

$(LIB): $(OBJ)
	mkdir -p build
	ar rcs $@ $^

build/%.o: src/%.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(CLI): tools/cli.cpp $(LIB)
	$(CXX) $(CXXFLAGS) $< -Lbuild -ltriedb -o $@

clean:
	rm -rf build