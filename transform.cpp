#include "sudoku.h"
#include <iostream>
using namespace std;
int main() {
    ios::sync_with_stdio (false);
    cin.tie (0);
    Sudoku s;
    s.read();
    int instruction, x, y;
    do {
        cin >> instruction;
        switch (instruction) {
        case 1:
            cin >> x >> y;
            s.swapNum(x, y);
            break;
        case 2:
            cin >> x >> y;
            s.swapRow(x, y);
            break;
        case 3:
            cin >> x >> y;
            s.swapCol(x, y);
            break;
        case 4:
            cin >> x;
            s.rotate(x);
            break;
        case 5:
            cin >> x;
            s.flip(x);
            break;
        }
    } while(instruction);
    s.write();
    return 0;
}
