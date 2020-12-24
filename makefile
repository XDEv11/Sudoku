# Provided by D4nnyLee

# Pre-defined variables for implicit rules
CXX := g++
CXXFLAGS := -std=c++17 -Ofast #-Wall -Wextra --debug -fsanitize=address,undefined -D_GLIBCXX_DEBUG

all: solve

# Specify additional dependency for implicit rules to generate target files
solve: sudoku.o
sudoku.o: sudoku.h

clean:
	rm -f *.o
	rm -f solve
