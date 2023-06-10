#ifndef BOARD_H
#define BOARD_H

#include <string>

class Piece;

class Board {
public:
    Piece* theBoard[8][8];
    
    Board(bool blankBoard = false);
    ~Board();
    Board(const Board &other);
    // needed for graphicsrender.cc
    Board& operator=(Board &&other);

    bool validBoard();

    bool check(std::string team);
    bool checkmate(std::string team);
    bool stalemate(std::string team);
    bool twoKing();

    bool validmove(std::string team, int *cur, int *dest, bool &canCheck, bool &captureEnemy, bool &escape, bool &canCheckmate, std::string newType);
    // user will need to free (delete) the returned Board*
    Board* moveto(int *cur, int *dest, std::string newType);
    
    void setUndercap();
};


std::ostream& operator<<(std::ostream &out, Board *board);

#endif
