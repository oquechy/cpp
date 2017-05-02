#ifndef HW2_BOARDTEST_H
#define HW2_BOARDTEST_H

#include "Test.h"
#include "../src/BoardView.h"
/*Board();
    void move(int x, int y, char sign); //сделать ход
    bool canMove(int x, int y, char sign); //корректен ли ход
    state isWin(); // текущее состояние: играем дальше; ничья; 0 выиграли; X выиграли
    char Cell(int x, int y);
    //Можно добавлять методы при необходимости.
*/

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
};

#endif //HW2_BOARDTEST_H
