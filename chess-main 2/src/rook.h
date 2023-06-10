#ifndef ROOK_H
#define ROOK_H

#include "piece.h"

class Rook: public Piece {
public:
    Rook(int row, int col, std::string team, bool undercap, bool moved);
    bool validmove(Board &board, int *dest, bool suicide, bool &canCheck, bool &captureEnemy, bool &escape, bool &canCheckmate, std::string newType) override;
};

#endif
