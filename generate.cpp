#include "sudoku.h"
#include <iostream>
#include <ctime>
using namespace std;
int main() {
    ios::sync_with_stdio (false);
    cin.tie (0);
    srandom(time(NULL));
    Sudoku s = Sudoku::generate();
    s.write();
    return 0;
}
