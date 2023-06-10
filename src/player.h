#ifndef PLAYER_H
#define PLAYER_H

#include <string>

class Board;

class Player {
protected:
    std::string team;
public:
    explicit Player(std::string team);
    virtual ~Player();
    virtual Board* move(Board* gameBoard, bool &success) = 0;
};

#endif
