#ifndef HW2_BOARD_H
#define HW2_BOARD_H

enum state{
    X_WIN,
    O_WIN,
    DRAW,
    CONT
};

class Board {
private:
    char _field[10][10];

public:
    Board();
    void move(int x, int y, char sign); //сделать ход
    bool canMove(int x, int y, char sign) const; //корректен ли ход
    state isWin() const; // текущее состояние: играем дальше; ничья; 0 выиграли; X выиграли
    char Cell(int x, int y) const;
    //Можно добавлять методы при необходимости.
};

#endif //HW2_BOARD_H
