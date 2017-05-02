/*#ifndef HW2_BOARD_H
#define HW2_BOARD_H

enum state{
    X_WIN,
    O_WIN,
    DRAW,
    CONT
};

class  Board {
public:
    void move(int x, int y, char sign); //сделать ход
    bool canMove(int x, int y, char sign); //корректен ли ход
    state isWin(); // текущее состояние: играем дальше; ничья; 0 выиграли; X выиграли
    char Cell(int x, int y);
    //Можно добавлять методы при необходимости.
};

#endif //HW2_BOARD_H
*/
#include "Board.h"

Board::Board() {
    for (int i = 0; i < 10; ++i)
        for (int j = 0; j < 10; ++j)
            _field[i][j] = '.';
}

bool Board::canMove(int x, int y, char sign) const { //корректен ли ход
    return (0 <= x && x < 10 && 0 <= y && y < 10 && _field[x][y] == '.' && (sign == 'X' || sign == 'O'));
}

void Board::move(int x, int y, char sign) { //сделать ход
    _field[x][y] = sign;
}

state Board::isWin() const { // текущее состояние: играем дальше; ничья; 0 выиграли; X выиграли
    bool done = 1;
    for (int i = 0; i < 10; ++i)
        for (int j = 0; j < 10; ++j) {
            if (_field[i][j] == '.') {
                done = 0;
                continue;
            }
            bool w[4] = {1, 1, 1, 1};
            for (int q = 1; q < 5; ++q) {
                w[0] &= (i + q < 10 && _field[i][j] == _field[i + q][j]);
                w[1] &= (j + q < 10 && _field[i][j] == _field[i][j + q]);
                w[2] &= (i + q < 10 && j + q < 10 && _field[i][j] == _field[i + q][j + q]);
                w[3] &= (i + q < 10 && 0 <= j - q && _field[i][j] == _field[i + q][j - q]);
            }
            if (w[0] || w[1] || w[2] || w[3])
                return (_field[i][j] == 'X' ? X_WIN : O_WIN);
        }
    return (done ? DRAW : CONT);
 }

char Board::Cell(int x, int y) const {
    return _field[x][y];
}
