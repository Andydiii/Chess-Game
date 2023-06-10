#ifndef CHESS_H
#define CHESS_H

#include "subject.h"
#include <string>

class Player;
class Board;

class Chess: public Subject {
    std::string curPlayer;
    bool gameRunning;
    bool gameStart;
    Board* curBoard;
    Board* prevBoard;
    Player* white;
    Player* black;

    void reset();
    
public:
    float whiteWin;
    float blackWin;
    
    Chess();
    ~Chess() override;
    void takeTurn();
    Board* getState() override;
};

#endif
