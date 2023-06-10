#ifndef PIECE_H
#define PIECE_H

#include <string>

class Board;

class Piece {
protected:
    // make sure this is does NOT live on heap
    int pos[2];
    std::string team;  // black, white
    std::string type;  // king, queen, bishop, rook, knight, pawn
    bool undercap;
    bool moved;
    bool canEnpassant;

public:
    // int pos[2];
    // bool canEnpassant;

    Piece(int row, int col, std::string team, std::string type, bool undercap, bool moved, bool canEnpassant);
    virtual ~Piece();
    std::string getTeam();
    std::string getType();

    bool getUndercap();
    void setUndercap(Board &board);

    bool getMoved();
    void setMoved(bool status);
    bool getEnpassant();
    void setEnpassant(bool status);

    // return true as long as it obey moving rules and doesnt put own king in check
    // how to check if own king is in check? see notes.txt
    virtual bool validmove(Board &board, int *dest, bool suicide, bool &canCheck, bool &captureEnemy, bool &escape, bool &canCheckmate, std::string newType) = 0;
    
    // return a new dynamically allocated board, user need to delete
    // OOOOOOOOOOOOOONLY OVERRIDE IN KING(castle) AND PAWN(enpassant)
    // should set all canEnpassant=false
    virtual Board* moveto(Board &board, int *dest, std::string newType);

    // OOOOOOOOOOOOOONLY OVERRIDE IN KING
    virtual bool getUndercheck(Board &board);
};

#endif
