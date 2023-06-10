#ifndef ROBOT4_H
#define ROBOT4_H

#include "player.h"

class Robot4: public Player {
public:
    Robot4(std::string team);
    Board* move(Board *gameBoard, bool &success) override;
};

#endif
