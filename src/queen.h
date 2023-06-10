#ifndef QUEEN_H
#define QUEEN_H

#include "piece.h"

class Queen: public Piece {
public:
    Queen(int row, int col, std::string team, bool undercap, bool moved);
    bool validmove(Board &board, int *dest, bool destIsKing, bool &canCheck, bool &captureEnemy, bool &escape, bool &canCheckmate, std::string newType) override;
};

#endif
