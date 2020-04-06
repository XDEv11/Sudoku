#ifndef SUDOKU_H
#define SUDOKU_H
class Sudoku {
  public:
    bool read();
    void write();
    void write_s();

    // generate
    static Sudoku generate();

    // transform
    void swapNum(int, int);
    void swapRow(int, int);
    void swapCol(int, int);
    void rotate(int);
    void flip(int);

    // solve
    void solve();
  private:
    bool equal_test();
    bool DFS();

  private:
    int filled = 0;
    int m[81];
    int nop[81];//the number of possible numbers to fill in.
    bool poss[729];//possible number to fill in~if n is the possible number to fill in, then poss[row * 81+column * 9+ (n-1) ] is true;
    int number_of_solution = 0;//0 for none, 1 for solo, 2 for multiple.
    int first_s[81];
    void set(int, int, int);

};
#endif
