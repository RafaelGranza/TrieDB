CXX = g++
CXXFLAGS = -O3 -std=c++20 -Wall -Iinclude

SRC = $(wildcard src/*.cpp)
OBJ = $(patsubst src/%.cpp,build/%.o,$(SRC))

LIB = build/libtriedb.a

CLI = build/triedb-cli

$(CLI): tools/triebd_cli.cpp $(LIB)
	$(CXX) $(CXXFLAGS) $< -Lbuild -ltriedb -o $@

all: $(LIB) $(CLI)

$(LIB): $(OBJ)
	ar rcs $@ $^

build/%.o: src/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf build

.PHONY: all clean