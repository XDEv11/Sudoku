#include "sudoku.h"
#include <iostream>
#include <algorithm>

using namespace std;

bool Sudoku::read() {
    filled = 0;
    numOfSol = 0;
    for (int r{0}; r < 9; ++r)
        for (int c{0}; c < 9; ++c) {
            if (!(cin >> grid[r][c]) || grid[r][c] < 0 || grid[r][c] > 9) return false; // EOF or out of range
            if (grid[r][c]) {
                ++filled;
                cnt[r][c] = -1;
                for (int n{1}; n <= 9; ++n) poss[r][c][n - 1] = false;
            } else { // empty block
                cnt[r][c] = 9;
                for (int n{1}; n <= 9; ++n) poss[r][c][n - 1] = true;
            }
        }
	canBeSolved = true;
    return true;
}

inline void print(const Sudoku::board<int>& b) {
	cout << "\e(0";
	cout << "lqqwqqwqqwqqwqqwqqwqqwqqwqqk\n";
	for (int r{0}; r < 9; ++r) {
		cout << "x ";
		for (int c{0}; c < 9; ++c)
			if (b[r][c]) cout << b[r][c] << "x ";
			else cout << " x ";
		if (r == 8) cout << "\nmqqvqqvqqvqqvqqvqqvqqvqqvqqj\n";
		else cout << "\ntqqnqqnqqnqqnqqnqqnqqnqqnqqu\n";
	}
	cout << "\e(B";
	// cout.flush();
}

void Sudoku::printQ() { // write question
	print(grid);
}

void Sudoku::printSol() { // write solution
    if (numOfSol == 0) cout << "No solution.\n";
	else if (numOfSol == 1) {
			cout << "Unique solution.\n";
			print(firstSol);
	} else cout << "Multiple solutions.\n";
}

void Sudoku::set(int r, int c, int n) {
	for (int i{0}; i < 9; ++i) {
		if (poss[r][i][n - 1]) {
			poss[r][i][n - 1] = false;
			--cnt[r][i];
		}
		if (poss[i][c][n - 1]) {
			poss[i][c][n - 1] = false;
			--cnt[i][c];
		}
	}
	int sr{r / 3}, sc{c / 3};
	for (int i{3 * sr}; i < 3 * sr + 3; ++i)
		for (int j{3 * sc}; j < 3 * sc + 3; ++j)
			if (poss[i][j][n - 1]) {
				poss[i][j][n - 1] = false;
				--cnt[i][j];
			}
}

void Sudoku::fill(int r, int c, int n) {
	grid[r][c] = n;
	for (int n{1}; n <= 9; ++n) poss[r][c][n - 1] = false;
	cnt[r][c] = -1;
	++filled;
	set(r, c, n);
}

bool Sudoku::checkAndFill()  {
	array<int, 9> test;
CONTINUE:
// normal check
    for (int r{0}; r < 9; ++r)
		for (int c{0}; c < 9; ++c)
			if (cnt[r][c] == 0) return false; // none
			else if (cnt[r][c] == 1) { // solo
				for (int n{1}; n <= 9; ++n)
					if (poss[r][c][n - 1]) {
						fill(r, c, n);
						goto CONTINUE;
					}
			}
// special check
	for (int r{0}; r < 9; ++r) { // row
		for (int n{1}; n <= 9; ++n) test[n - 1] = 0;
		for (int c{0}; c < 9; ++c)
			for (int n{1}; n <= 9; ++n)
				if (poss[r][c][n - 1]) test[n - 1] += 1;
		for (int c{0}; c < 9; ++c)
			if (grid[r][c]) test[grid[r][c] - 1] = -1;

		for (int n{1}; n <= 9; ++n) {
			if (test[n - 1] == 0) return false; // none
			else if (test[n - 1] == 1) { // solo
				for (int c{0}; c < 9; ++c)
					if (poss[r][c][n - 1]) {
						fill(r, c, n);
						goto CONTINUE;
					}
			}
		}
	}

	for (int c{0}; c < 9; ++c) { // column
		for (int n{1}; n <= 9; ++n) test[n - 1] = 0;
		for (int r{0}; r < 9; ++r)
			for (int n{1}; n <= 9; ++n)
				if (poss[r][c][n - 1]) test[n - 1] += 1;
		for (int r{0}; r < 9; ++r)
			if (grid[r][c]) test[grid[r][c] - 1] = -1;

		for (int n{1}; n <= 9; ++n) {
			if (test[n - 1] == 0) return false; // none
			else if (test[n - 1] == 1) { // solo
				for (int r{0}; r < 9; ++r)
					if (poss[r][c][n - 1]) {
						fill(r, c, n);
						goto CONTINUE;
					}
			}
		}
	}

	for (int sr{0}; sr < 3; ++sr) {
		for (int sc{0}; sc < 3; ++sc) { // subgrid
			for (int n{1}; n <= 9; ++n) test[n - 1] = 0;
			for (int r{3 * sr}; r < 3 * sr + 3; ++r)
				for (int c{3 * sc}; c < 3 * sc + 3; ++c)
					for (int n{1}; n <= 10; ++n)
						if (poss[r][c][n - 1]) test[n - 1] += 1;
			for (int r{3 * sr}; r < 3 * sr + 3; ++r)
				for (int c{3 * sc}; c < 3 * sc + 3; ++c)
					if (grid[r][c]) test[grid[r][c] - 1] = -1;

			for (int n{1}; n <= 9; ++n) {
				if (test[n - 1] == 0) return false; // none
				else if (test[n - 1] == 1) { // solo
					for (int r{3 * sr}; r < 3 * sr + 3; ++r)
						for (int c{3 * sc}; c < 3 * sc + 3; ++c)
							if (poss[r][c][n - 1]) {
								fill(r, c, n);
								goto CONTINUE;
							}
				}
			}
		}
	}
	return true;
}

bool Sudoku::DFS() {
	if (filled == 81) {//find a solution
		++numOfSol;
		if (numOfSol == 1) { // first solution
			firstSol = grid;
			return true;
		} else return false;
	}

    int min_cnt = 10, fr, fc;
	auto Rfilled{filled};
	auto Rgrid{grid};
	auto Rcnt{cnt};
	auto Rposs{poss};
	for (int r{0}; r < 9; ++r)
		for (int c{0}; c < 9; ++c)
			if (cnt[r][c] != -1 && cnt[r][c] < min_cnt) { // find a block with least possibility
				min_cnt = cnt[r][c];
				fr = r;
				fc = c;
			}
	for (int n{1}; n <= 9; ++n) {
		if (poss[fr][fc][n - 1]) { // try to fill this block
			fill(fr, fc, n);
			if (checkAndFill() == false || DFS() == true) { // wrong try, return to the last status
				Rposs[fr][fc][n - 1] = false;
				--Rcnt[fr][fc];
				
				filled = Rfilled;
				grid = Rgrid;
				cnt = Rcnt;
				poss = Rposs;
			} else return false;
		}
	}
	return true;
}

void Sudoku::solve() {
	if (!canBeSolved) return ;

	for (int r{0}; r < 9; ++r)
		for (int c{0}; c < 9; ++c)
			if (grid[r][c]) set(r, c, grid[r][c]);
	if (checkAndFill() == false) numOfSol = 0;
	else if (filled < 17) numOfSol = 2;
	else DFS();

	canBeSolved = false;
}
