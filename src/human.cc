#include <iostream>
#include "human.h"
#include "piece.h"
#include "board.h"

using namespace std;

Human::Human(string team):
    Player{team}
{}


Board* Human::move(Board* gameBoard, bool &success) {    
    string command;
    string posS;
    string destS;
    
    // start position
    cin >> posS;
    cin >> destS;

    if ('a' <= posS[0] && posS[0] <= 'h' && '1' <= posS[1] && posS[1] <= '8') {
        if ('a' <= destS[0] && destS[0] <= 'h' && '1' <= destS[1] && destS[1] <= '8') {
            int pos[] = {posS[1] - '1', posS[0] - 'a'};
            int dest[] = {destS[1] - '1', destS[0] - 'a'};
            bool fake;
            // this validmove check could be pawn promotion, use queen as placeholder, acutal type is used later
            if (gameBoard->validmove(team, pos, dest, fake, fake, fake, fake, "queen")) {
                Piece *curpiece = gameBoard->theBoard[pos[0]][pos[1]];

                if (curpiece->getType() == "pawn" && (dest[0] == 0 || dest[0] == 7)) {
                    // pawn promotion
                    string promotionType;
                    cin >> promotionType;
                    
                    if ((team == "white" && promotionType != "Q" && promotionType != "R" && promotionType != "B" && promotionType != "N") ||
                    (team == "black" && promotionType != "q" && promotionType != "r" && promotionType != "b" && promotionType != "n")) {
                        cout << "invalid piece type" << endl;
                        success = false;
                        return nullptr;
                    }

                    if (promotionType == "Q" || promotionType == "q") {
                        promotionType = "queen";
                    } else if (promotionType == "R" || promotionType == "r") {
                        promotionType = "rook";
                    } else if (promotionType == "B" || promotionType == "b") {
                        promotionType = "bishop";
                    } else if (promotionType == "N" || promotionType == "n") {
                        promotionType = "knight";
                    }
                    
                    success = true;
                    return gameBoard->moveto(pos, dest, promotionType);

                } else {
                    success = true;
                    // non-promotion move, DNE will not be used
                    return gameBoard->moveto(pos, dest, "DNE");
                }
            }
        }
    }
    cout << "invalid command, move is not accepted" << endl;
    // if reach here, then we know move is not valid, the returned nullptr should not be used
    success = false;
    return nullptr;
}
