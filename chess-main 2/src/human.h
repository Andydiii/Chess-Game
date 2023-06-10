#ifndef HUMAN_H
#define HUMAN_H

#include "player.h"

class Human: public Player {
public:
    Human(std::string team);
    Board* move(Board* gameBoard, bool &success) override;
};

#endif
