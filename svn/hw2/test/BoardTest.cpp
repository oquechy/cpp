#include "BoardTest.h"
#include <cstdlib>
/*
class BoardTest : public Test {
public:
    void runAllTests();
    void moveTest1();
    void moveTest2();
    void moveTest3();
    void canMoveTest1();
    void canMoveTest2();
    void canMoveTest3();
    void isWinTest1();
    void isWinTest2();
    void isWinTest3();
    void cellTest1();
    void cellTest2();
    void cellTest3();
};*/

void BoardTest::runAllTests() {
    moveTest1();
    moveTest2();
    moveTest3();
    canMoveTest1();
    canMoveTest2();
    canMoveTest3();
    isWinTest2();
    isWinTest1();
    isWinTest3();
    cellTest1();
    cellTest2();
    cellTest3();
}

void BoardTest::moveTest1() {
    Board b;
    b.move(5, 5, 'X');
    for (int i = 0; i < 10; ++i)
        for (int j = 0; j < 10; ++j)
            if (i == 5 && j == 5)
                DO_CHECK(b.Cell(5, 5) == 'X');
            else
                DO_CHECK(b.Cell(i, j) == '.');
}

void BoardTest::moveTest2() {
    Board b;
    b.move(0, 9, 'O');
    for (int i = 0; i < 10; ++i)
        for (int j = 0; j < 10; ++j)
            if (i == 0 && j == 9)
                DO_CHECK(b.Cell(0, 9) == 'O');
            else
                DO_CHECK(b.Cell(i, j) == '.');
}

void BoardTest::moveTest3() {
    Board b;
    b.move(9, 9, 'X');
    b.move(1, 1, 'O');
    for (int i = 0; i < 10; ++i)
        for (int j = 0; j < 10; ++j)
            if (i == 1 && j == 1)
                DO_CHECK(b.Cell(1, 1) == 'O');
            else if (i == 9 && j == 9)
                DO_CHECK(b.Cell(9, 9) == 'X');
            else
                DO_CHECK(b.Cell(5, 5) == '.');
}

void BoardTest::canMoveTest1() {
    Board b;
    b.move(0, 0, 'X');
    DO_CHECK(!b.canMove(0, 0, 'O'));
}

void BoardTest::canMoveTest2() {
    Board b;
    b.move(4, 4, 'O');
    b.move(4, 5, 'O');
    b.move(4, 6, 'X');
    b.move(5, 4, 'X');
    b.move(5, 6, 'O');
    b.move(6, 4, 'O');
    b.move(6, 5, 'O');
    b.move(6, 6, 'X');
    DO_CHECK(b.canMove(5, 5, 'X'));
}

void BoardTest::canMoveTest3() {
    Board b;
    b.move(4, 4, 'O');
    b.move(4, 5, 'O');
    b.move(4, 6, 'X');
    b.move(5, 4, 'X');
    b.move(5, 5, 'O');
    b.move(5, 6, 'O');
    b.move(6, 4, 'O');
    b.move(6, 5, 'O');
    b.move(6, 6, 'X');
    DO_CHECK(!b.canMove(5, 5, 'O'));
}

void BoardTest::isWinTest1() {
    Board b;
    b.move(6, 5, 'X');
    b.move(7, 6, 'X');
    b.move(8, 7, 'X');
    b.move(9, 8, 'X');
    b.move(5, 4, 'X');
    b.move(4, 3, 'O');
    b.move(7, 3, 'O');
    b.move(4, 8, 'O');
    b.move(1, 3, 'O');
    b.move(4, 5, 'O');
    DO_CHECK(b.isWin() == X_WIN);
}

void BoardTest::isWinTest2() {
    Board b;
    b.move(6, 5, 'X');
    b.move(7, 6, 'X');
    b.move(8, 7, 'O');
    b.move(9, 8, 'X');
    b.move(5, 4, 'X');
    b.move(4, 3, 'O');
    b.move(7, 3, 'O');
    b.move(4, 8, 'O');
    b.move(1, 3, 'X');
    b.move(0, 5, 'O');
    b.move(1, 5, 'O');
    b.move(2, 5, 'O');
    b.move(3, 5, 'O');
    b.move(5, 5, 'O');
    DO_CHECK(b.isWin() == CONT);
}

void BoardTest::isWinTest3() {
    Board b;
    char c[] = "XO";
    for (int i = 0; i < 10; ++i)
        for (int j = 0; j < 10; ++j)
            b.move(i, j, c[((i / 2 + j)) % 2]);
    DO_CHECK(b.isWin() == DRAW);
}

void BoardTest::cellTest1() {
    Board b;
    DO_CHECK(b.Cell(2, 0) == '.');
}

void BoardTest::cellTest2() {
    Board b;
    b.move(5, 5, 'X');
    DO_CHECK(b.Cell(5, 5) == 'X');
}

void BoardTest::cellTest3() {
    Board b;
    b.move(9, 0, 'O');
    b.move(8, 0, 'X');
    DO_CHECK(b.Cell(9, 0) == 'O');
}
