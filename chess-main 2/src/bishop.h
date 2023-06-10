#ifndef BISHOP_H
#define BISHOP_H

#include "piece.h"

class Bishop: public Piece {
public:
    Bishop(int row, int col, std::string team, bool undercap, bool moved);
    bool validmove(Board &board, int *dest, bool suicide, bool &canCheck, bool &captureEnemy, bool &escape, bool &canCheckmate, std::string newType) override;
};

#endif
