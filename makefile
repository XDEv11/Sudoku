all: generate transform solve
generate: sudoku.h sudoku.cpp generate.cpp
	astyle --style=google --indent=spaces=4 --suffix=none sudoku.h sudoku.cpp generate.cpp
	g++ -c sudoku.cpp
	g++ -c generate.cpp
	g++ sudoku.o generate.o -o generate
	rm *.o
transform: sudoku.h sudoku.cpp transform.cpp
	astyle --style=google --indent=spaces=4 --suffix=none  sudoku.h sudoku.cpp transform.cpp
	g++ -c sudoku.cpp
	g++ -c transform.cpp
	g++ sudoku.o transform.o -o transform
	rm *.o
solve: sudoku.h sudoku.cpp solve.cpp
	astyle --style=google --indent=spaces=4 --suffix=none sudoku.h sudoku.cpp solve.cpp
	g++ -c sudoku.cpp
	g++ -c solve.cpp
	g++ sudoku.o solve.o -o solve
	rm *.o
clean:
	rm generate transform solve
