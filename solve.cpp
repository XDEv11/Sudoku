#include "sudoku.h"
#include <iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	auto b = system_clock::now();
	Sudoku s{};
	while (s.read()) {
		// s.printQ();
		s.solve();
		s.printSol();
	}
	auto e = system_clock::now();
	cout << duration_cast<milliseconds>(e - b).count() << " ms\n";

	return 0;
}
