all: solve
solve: sudoku.o solve.o
	g++ sudoku.o solve.o -o solve
sudoku.o: sudoku.h sudoku.cpp
	g++ -c sudoku.cpp -Ofast
solve.o: sudoku.h solve.cpp
	g++ -c solve.cpp
clean:
	rm *.o
	rm solve
