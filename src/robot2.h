#ifndef ROBOT2_H
#define ROBOT2_H

#include "player.h"

class Robot2: public Player {
public:
    Robot2(std::string team);
    Board* move(Board *gameBoard, bool &success) override;
};


#endif
