#ifndef ROBOT1_H
#define ROBOT1_H

#include "player.h"

class Robot1: public Player {
public:
    Robot1(std::string team);
    Board* move(Board *gameBoard, bool &success) override;
};

#endif
