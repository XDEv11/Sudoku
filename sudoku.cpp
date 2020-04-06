#include "sudoku.h"
#include <iostream>
#include <ctime>
using namespace std;

bool Sudoku::read() {
    int row, column, i;
    filled = 0;
    number_of_solution = 0;
    for (row = 0; row < 9; ++row)
        for (column = 0; column < 9; ++column) {
            if (!(cin >> m[row * 9 + column])) return false;//EOF
            if (m[row * 9 + column] < 0 || m[row * 9 + column] > 9) return false;//out of range
            if (m[row * 9 + column]) {//filled_block
                ++filled;
                nop[row * 9 + column] = -1;
                for (int i = 1; i < 10; ++i) poss[row * 81 + column * 9 + (i - 1)] = false;
            } else {//empty_block
                nop[row * 9 + column] = 9;
                for (int i = 1; i < 10; ++i) poss[row * 81 + column * 9 + (i - 1)] = true;
            }
        }
    return true;
}

void Sudoku::write() {
    int row, column;
    for (row = 0; row < 9; ++row)
        for (column = 0; column < 9; ++column) cout << m[row * 9 + column] << (column == 8? '\n':' ' );
}

void Sudoku::write_s() {//write solution
    cout << number_of_solution << '\n';
    if (number_of_solution != 1) return ;
    int row, column;
    for (row = 0; row < 9; ++row)
        for (column = 0; column < 9; ++column) cout << first_s[row * 9 + column] << (column == 8? '\n':' ' );
}

//begin of generate
Sudoku Sudoku::generate() {
    Sudoku s;
    s.filled = 0;
    s.number_of_solution = 0;
    int row, column, i, rand;
    int g[243] = {5, 0, 0, 6, 0, 0, 0, 0, 0,
                  0, 0, 0, 1, 0, 0, 0, 3, 0,
                  0, 0, 4, 0, 0, 0, 0, 2, 0,
                  0, 0, 0, 0, 0, 0, 0, 0, 0,
                  0, 2, 0, 0, 0, 0, 7, 0, 0,
                  1, 6, 0, 5, 0, 0, 0, 0, 0,
                  0, 0, 0, 0, 0, 0, 6, 0, 0,
                  0, 0, 0, 0, 3, 0, 0, 0, 1,
                  0, 0, 8, 0, 4, 0, 5, 0, 0,//
                  8, 0, 0, 0, 0, 0, 0, 0, 1,
                  0, 0, 0, 0, 6, 5, 0, 0, 0,
                  0, 0, 0, 0, 0, 0, 0, 7, 0,
                  0, 6, 7, 0, 3, 0, 0, 0, 0,
                  0, 0, 0, 4, 0, 0, 5, 0, 0,
                  0, 0, 0, 0, 0, 0, 2, 0, 0,
                  0, 2, 0, 0, 0, 0, 0, 3, 0,
                  0, 0, 0, 0, 0, 7, 6, 0, 0,
                  4, 0, 0, 1, 0, 0, 0, 0, 0,//
                  0, 0, 5, 0, 0, 6, 0, 0, 0,
                  0, 0, 0, 0, 0, 1, 0, 3, 0,
                  4, 0, 0, 0, 0, 0, 0, 2, 0,
                  0, 0, 0, 0, 0, 0, 0, 0, 0,
                  0, 2, 0, 0, 0, 0, 0, 0, 7,
                  0, 6, 1, 0, 0, 5, 0, 0, 0,
                  0, 0, 0, 0, 0, 0, 0, 0, 6,
                  0, 0, 0, 0, 3, 0, 1, 0, 0,
                  8, 0, 0, 0, 4, 0, 0, 0, 5,//
                 };//init
    rand = random() % 3;
    for (row = 0; row < 9; ++row)
        for (column = 0; column < 9; ++column) {
            s.m[row * 9 + column] = g[rand * 81 + row * 9 + column];
            if (s.m[row * 9 + column]) {
                ++s.filled;
                s.nop[row * 9 + column] = -1;
                for (int i = 1; i < 10; ++i) s.poss[row * 81 + column * 9 + (i - 1)] = false;
            } else {
                s.nop[row * 9 + column] = 9;
                for (int i = 1; i < 10; ++i) s.poss[row * 81 + column * 9 + (i - 1)] = true;
            }
        }
    return s;
}
//end of generate

//begin of transform
void Sudoku::swapNum(int x, int y) {
    if (x > 9 || x < 1) return;
    if (y > 9 || y < 1) return;
    if (x == y) return;
    int row, column;
    for (row = 0; row < 9; ++row)
        for (column = 0; column < 9; ++column)
            if (m[row * 9 + column] == x) m[row * 9 + column] = y;
            else if (m[row * 9 + column] == y) m[row * 9 + column] = x;
}

void Sudoku::swapRow(int x, int y) {
    if (x > 2 || x < 0) return;
    if (y > 2 || y < 0) return;
    if (x == y) return;
    x = 3 * x;
    y = 3 * y;
    int column, temp[9];
    for (column = 0; column < 9; ++column) temp[column] = m[x * 9 + column];
    for (column = 0; column < 9; ++column) m[x * 9 + column] = m[y * 9 + column];
    for (column = 0; column < 9; ++column) m[y * 9 + column] = temp[column];
    for (column = 0; column < 9; ++column) temp[column] = m[(x + 1) * 9 + column];
    for (column = 0; column < 9; ++column) m[(x + 1) * 9 + column] = m[(y + 1) * 9 + column];
    for (column = 0; column < 9; ++column) m[(y + 1) * 9 + column] = temp[column];
    for (column = 0; column < 9; ++column) temp[column] = m[(x + 2) * 9 + column];
    for (column = 0; column < 9; ++column) m[(x + 2) * 9 + column] = m[(y + 2) * 9 + column];
    for (column = 0; column < 9; ++column) m[(y + 2) * 9 + column] = temp[column];
}

void Sudoku::swapCol(int x, int y) {
    if (x > 2 || x < 0) return;
    if (y > 2 || y < 0) return;
    if (x == y) return;
    x = 3 * x;
    y = 3 * y;
    int row, temp[9];
    for (row = 0; row < 9; ++row) temp[row] = m[row * 9 + x];
    for (row = 0; row < 9; ++row) m[row * 9 + x] = m[row * 9 + y];
    for (row = 0; row < 9; ++row) m[row * 9 + y] = temp[row];
    for (row = 0; row < 9; ++row) temp[row] = m[row * 9 + (x + 1)];
    for (row = 0; row < 9; ++row) m[row * 9 + (x + 1)] = m[row * 9 + (y + 1)];
    for (row = 0; row < 9; ++row) m[row * 9 + (y + 1)] = temp[row];
    for (row = 0; row < 9; ++row) temp[row] = m[row * 9 + (x + 2)];
    for (row = 0; row < 9; ++row) m[row * 9 + (x + 2)] = m[row * 9 + (y + 2)];
    for (row = 0; row < 9; ++row) m[row * 9 + (y + 2)] = temp[row];
}

void Sudoku::rotate(int x) {
    while (x > 3 || x < 0) {
        if (x > 0) x = x % 4;
        if (x < 0) x += 4;
    }
    int row, column, i, temp[81];
    for (i = 0; i < x; ++i) {
        for (row = 0; row < 9; ++row)
            for (column = 0; column < 9; ++column) temp[row * 9 + (8 - column)] = m[column * 9 + row];
        for (row = 0; row < 9; ++row)
            for (column = 0; column < 9; ++column) m[row * 9 + column] = temp[row * 9 + column];
    }
}

void Sudoku::flip(int x) {
    if (x > 1 || x < 0) return;
    int row, column, temp[81];
    for (row = 0; row < 9; ++row)
        for (column = 0; column < 9; ++column)
            if(x) temp[row * 9 + 8 - column] = m[row * 9 + column];
            else temp[(8 - row) * 9 + column] = m[row * 9 + column];
    for (row = 0; row < 9; ++row)
        for (column = 0; column < 9; ++column) m[row * 9 + column] = temp[row * 9 + column];
}
//end of transform

//begin of solve
void Sudoku::set(int row, int column, int n) {
    int i, j, subgrid_row, subgrid_column;
    for(i = 0; i < 9; ++i) {
        if (poss[row * 81 + i * 9 + (n - 1)] == true) {
            poss[row * 81 + i * 9 + (n - 1)] = false;
            --nop[row * 9 + i];
        }
        if (poss[i * 81 + column * 9 + (n - 1)] == true) {
            poss[i * 81 + column * 9 + (n - 1)] = false;
            --nop[i * 9 + column];
        }
    }
    subgrid_row = row / 3;
    subgrid_column = column / 3;
    for (i = 3 * subgrid_row; i < 3 * subgrid_row + 3; ++i)
        for(j = 3 * subgrid_column; j < 3 * subgrid_column + 3; ++j)
            if (poss[i * 81 + j * 9 + (n - 1)] == true) {
                poss[i * 81 + j * 9 + (n - 1)] = false;
                --nop[i * 9 + j];
            }
}

//Fill the block that has one possible number left, and return false while there is a block that can't be filled.
bool Sudoku::equal_test()  {
//normal_test
    int row, column, n, i, j, test[9], subgrid_row, subgrid_column;
    bool flag;
    do {
        flag = false;
        for (row = 0; row < 9; ++row)
            for (column = 0; column < 9; ++column)
                if (nop[row * 9 + column] == 0) return false;//none
                else if (nop[row * 9 + column] == 1) {//solo possibility
                    for (n = 1; n < 10; ++n)
                        if(poss[row * 81 + column * 9 + (n - 1)] == true) {
                            m[row * 9 + column] = n;
                            poss[row * 81 + column * 9 + (n - 1)] = false;
                            nop[row * 9 + column] = -1;
                            ++filled;
                            set(row, column, n);
                            flag = true;
                            goto restart;
                        }
                }
//special_test
        for (row = 0; row < 9; ++row) { //test row
            for (n = 1; n < 10; ++n) test[n - 1] = 0;//init
            for (column = 0; column < 9; ++column)
                for (n = 1; n < 10; ++n) test[n - 1] += (poss[row * 81 + column * 9 + (n - 1)] == true ? 1:0);
            for (column = 0; column < 9; ++column)
                if (m[row * 9 + column]) test[m[row * 9 + column] - 1] = -1;
            for (n = 1; n < 10; ++n) {
                if (test[n - 1] == 0) return false;//none
                else if (test[n - 1] == 1) {//solo possibility
                    for (column = 0; column < 9; ++column)
                        if(poss[row * 81 + column * 9 + (n - 1)] == true) {
                            m[row * 9 + column] = n;
                            for (int i = 1; i < 10; ++i) poss[row * 81 + column * 9 + (i - 1)] = false;
                            nop[row * 9 + column] = -1;
                            ++filled;
                            set(row, column, n);
                            flag = true;
                            goto restart;
                        }
                }
            }
        }

        for (column = 0; column < 9; ++column) { //test column
            for (n = 1; n < 10; ++n) test[n - 1] = 0;//init
            for (row = 0; row < 9; ++row)
                for (n = 1; n < 10; ++n) test[n - 1] += (poss[row * 81 + column * 9 + (n - 1)] == true ? 1:0);
            for (row = 0; row < 9; ++row)
                if (m[row * 9 + column]) test[m[row * 9 + column] - 1] = -1;
            for (n = 1; n < 10; ++n) {
                if (test[n - 1] == 0) return false;//none
                else if (test[n - 1] == 1) {//solo possibility
                    for (row = 0; row < 9; ++row)
                        if(poss[row * 81 + column * 9 + (n - 1)] == true) {
                            m[row * 9 + column] = n;
                            for (int i = 1; i < 10; ++i) poss[row * 81 + column * 9 + (i - 1)] = false;
                            nop[row * 9 + column] = -1;
                            ++filled;
                            set(row, column, n);
                            flag = true;
                            goto restart;
                        }
                }
            }
        }

        for (subgrid_row = 0; subgrid_row < 3; ++subgrid_row) {
            for (subgrid_column = 0; subgrid_column < 3; ++subgrid_column) { //test subgrid
                for (n = 1; n < 10; ++n) test[n - 1] = 0;//init
                for (row = 3 * subgrid_row; row < 3 * subgrid_row + 3; ++row)
                    for (column = 3 * subgrid_column; column < 3 * subgrid_column + 3; ++column)
                        for(n = 1; n < 10; ++n) test[n - 1] += (poss[row * 81 + column * 9 + (n - 1)] == true ? 1:0);
                for (row = 3 * subgrid_row; row < 3 * subgrid_row + 3; ++row)
                    for (column = 3 * subgrid_column; column < 3 * subgrid_column + 3; ++column)
                        if (m[row * 9 + column]) test[m[row * 9 + column] - 1] = -1;
                for (n = 1; n < 10; ++n) {
                    if (test[n - 1] == 0) return false;//none
                    else if (test[n - 1] == 1) {//solo possibility
                        for (row = 3 * subgrid_row; row < 3 * subgrid_row + 3; ++row)
                            for (column = 3 * subgrid_column; column < 3 * subgrid_column + 3; ++column)
                                if(poss[row * 81 + column * 9 + (n - 1)] == true) {
                                    m[row * 9 + column] = n;
                                    for (int i = 1; i < 10; ++i) poss[row * 81 + column * 9 + (i - 1)] = false;
                                    nop[row * 9 + column] = -1;
                                    ++filled;
                                    set(row, column, n);
                                    flag = true;
                                    goto restart;
                                }
                    }
                }
            }
        }
restart:
        ;
    } while(flag);
    return true;
}

bool Sudoku::DFS() {
    int i, j, row, column, subgrid_row, subgrid_column, least_possibility = 10, r, c, rec_n, f = filled;
    int rec_m[81], rec_nop[81];
    bool rec_poss[729];
    if(filled < 81) {
        for (row = 0; row < 9; ++row)
            for (column = 0; column < 9; ++column) {
                rec_m[row * 9 + column] = m[row * 9 + column];//recording
                rec_nop[row * 9 + column] = nop[row * 9 + column];
                for (i = 1; i < 10; ++i)
                    rec_poss[row * 81 + column * 9 + (i - 1)] = poss[row * 81 + column * 9 + (i - 1)];
                if(nop[row * 9 + column] != -1 && nop[row * 9 + column] < least_possibility) {//find a block with least possibility
                    least_possibility = nop[row * 9 + column];
                    r = row;
                    c = column;
                }
            }
        for (int n = 1; n < 10; ++n) {
            if(poss[r * 81 + c * 9 + (n - 1)] == true) {//try to fill this block
                rec_n = m[r * 9 + c] = n;//
                for (int i = 1; i < 10; ++i) poss[r * 81 + c * 9 + (i - 1)] = false;
                nop[r * 9 + c] = -1;
                ++filled;
                set(r, c, n);
                if (equal_test() == false || DFS() == true) {//wrong try, return to the last status
                    //rec_poss[r * 81 + c * 9 + (rec_n - 1)] = false;//impossible
                    //--rec_nop[r * 9 + c];
                    for (row = 0; row < 9; ++row)
                        for (column = 0; column < 9; ++column) {
                            m[row * 9 + column] = rec_m[row * 9 + column];
                            nop[row * 9 + column] = rec_nop[row * 9 + column];
                            for (i = 1; i < 10; ++i)
                                poss[row * 81 + column * 9 + (i - 1)] = rec_poss[row * 81 + column * 9 + (i - 1)];
                        }
                    filled = f;
                } else return false;
            }
        }
        return true;
    } else {//find a solution
        ++number_of_solution;
        if(number_of_solution == 1) {//first_solution
            for (row = 0; row < 9; ++row)
                for (column = 0; column < 9; ++column) first_s[row * 9 + column] = m[row * 9 + column];
            return true;
        } else return false;
    }
}
void Sudoku::solve() {
    int rec_m[81], rec_nop[81];
    bool rec_poss[729];
    for (int row = 0; row < 9; ++row)//record
        for (int column = 0; column < 9; ++column) {
            rec_m[row * 9 + column] = m[row * 9 + column];
            rec_nop[row * 9 + column] = nop[row * 9 + column];
            for (int i = 1; i < 10; ++i)
                rec_poss[row * 81 + column * 9 + (i - 1)] = poss[row * 81 + column * 9 + (i - 1)];
        }
    for (int row = 0; row < 9; ++row)
        for (int column = 0; column < 9; ++column)
            if (m[row * 9 + column]) {
                set(row, column, m[row * 9 + column]);
            }
    if (equal_test() == false) number_of_solution = 0;
    else if(filled < 17) number_of_solution = 2;
    else DFS();
    for (int row = 0; row < 9; ++row)//resume
        for (int column = 0; column < 9; ++column) {
            m[row * 9 + column] = rec_m[row * 9 + column];
            nop[row * 9 + column] = rec_nop[row * 9 + column];
            for (int i = 1; i < 10; ++i)
                poss[row * 81 + column * 9 + (i - 1)] = rec_poss[row * 81 + column * 9 + (i - 1)];
        }
}
//end of solve
