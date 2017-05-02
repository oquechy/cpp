#include <iostream>
#include "matrix.h"

using namespace std;

int main() {
    const int N = 10;
    Matrix reg[N];
    string action;
    while (cin >> action) {
        if (action == "load") {
            char c;
            int r;
            string fname;
            cin >> c >> r >> fname;
            reg[r].load(fname);
        } else if (action == "print") {
            char c;
            int r;
            cin >> c >> r;
            reg[r].print();
        } else if (action == "add") {
            char c1, c2;
            int r1, r2;
            cin >> c1 >> r1 >> c2 >> r2;
            try {
                reg[r1].add(reg[r2]);
            }
            catch (MatrixException &e) {
                e.print(cout);
            }
        } else if (action == "mul") {
            char c1, c2;
            int r1, r2;
            cin >> c1 >> r1 >> c2 >> r2;
            try {
                reg[r1].mul(reg[r2]);
            }
            catch (MatrixException &e) {
                e.print(cout);
            }
        } else if (action == "elem") {
            char c;
            int r, i, j;
            cin >> c >> r >> i >> j;
            try {
                reg[r].elem(i, j);
            }
            catch (MatrixException &e) {
                e.print(cout);
            }
        } else if (action == "exit") {
            return 0;
        } else {
            cout << "usage:"
                    "\t\tload reg fname\n"
                    "\t\tprint reg\n"
                    "\t\tadd reg1 reg2\n"
                    "\t\tmul reg1 reg2\n"
                    "\t\telem reg i j\n"
                    "\t\texit\n";
        }
    }
}