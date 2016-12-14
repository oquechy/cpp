/*#ifndef HW2_BOARDVIEW_H
#define HW2_BOARDVIEW_H

#include "Board.h"

class View {
private:
    Board &_board;
public:
    View(Board &m);
    void showBoard(); //вывод доски на экран
    void doGameCycle(); //основной цикл игры: ввод хода, вывод на экран доски, проверка текущего состояния
};

#endif //HW2_BOARDVIEW_H
*/

#include "BoardView.h"
#include "cstdio"

View::View(Board &b) : _board(b) {}

void View::showBoard() { //вывод доски на экран
    printf("\n");
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j)
            printf("%c", _board.Cell(i, j));
        printf("\n");
    }
}

void View::doGameCycle(bool silent) { //основной цикл игры: ввод хода, вывод на экран доски, проверка текущего состояния
    char mode = 'O';
    int x, y;
    state res;
    while ((res = _board.isWin()) == CONT) {
        if (!silent)
            showBoard();
        printf("%c move: ", mode);
        while (scanf("%d %d", &x, &y) && !_board.canMove(x, y, mode) && (x != -1 || y != -1))
            printf("Bad move!\n%c move: ", mode);
        if (x == -1 && y == -1)
            return;
        _board.move(x, y, mode);
        mode = (mode == 'X' ? 'O' : 'X');
    }
    showBoard();
    if (res == O_WIN)
        printf("O wins!\n");
    else if (res == X_WIN)
        printf("X wins!\n");
    else
        printf("Draw.\n");
}
