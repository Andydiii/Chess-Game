#ifndef ROBOT3_H
#define ROBOT3_H

#include "player.h"

class Robot3: public Player {
public:
    Robot3(std::string team);
    Board* move(Board *gameBoard, bool &success) override;
};


#endif
