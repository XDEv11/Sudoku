#include "sudoku.h"
#include <iostream>
#include <ctime>

using namespace std;

int main() {
    ios_base::sync_with_stdio (false);
    cin.tie (0);
    Sudoku s;
    while(s.read()) {
        s.solve();
        s.write_s();
    }
    cout << "\ntime used = " << (float)clock() / CLOCKS_PER_SEC << "(s)\n";
    return 0;
}
