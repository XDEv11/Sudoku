#ifndef SUDOKU_H
#define SUDOKU_H

#include <array>
using std::array;

class Sudoku {
	template<typename T>
	using board = array<array<T, 9>, 9>;

public:
	explicit Sudoku() =default;
	bool read();
	void printQ();
	void printSol();
	void solve();

private:
	bool checkAndFill();
	bool DFS();

	board<int> grid;
	bool canBeSolved{false};
	int filled;
	int numOfSol;
	board<int> firstSol;
	board<int> cnt; // the number of possible numbers to fill in
	board<array<bool, 9>> poss; // poss[][i] == true implies number i+1 is possible for this entry
	void set(int, int, int);
	void fill(int, int, int);

};
#endif
