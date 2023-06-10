#include "robot1.h"
#include "board.h"
#include "piece.h"
#include <vector>

using namespace std;

Robot1::Robot1(string team):
    Player{team}
{}


Board* Robot1::move(Board *gameBoard, bool &success) {
    // robot will always have a valid move
    success = true;
    vector<string> regmove;

    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            int pos[] = {i, j};
            for (int desti = 0; desti < 8; ++desti) {
                for (int destj = 0; destj < 8; ++destj) {

                    int dest[] = {desti, destj};
                    Piece *p = gameBoard->theBoard[i][j];
                    bool fake;
                    
                    if (p != nullptr && p->getType() == "pawn" && (desti == 0 || desti == 7)) {
                        // check for potential pawn promotion, use "queen" as placeholder
                        if (gameBoard->validmove(team, pos, dest, fake, fake, fake, fake, "queen")) {
                            // robot1 add both pawn promotion to regmove
                            string queenPromo = to_string(i) + to_string(j) + to_string(desti) + to_string(destj) + "queen";
                            string knightPromo = to_string(i) + to_string(j) + to_string(desti) + to_string(destj) + "knight";
                            regmove.push_back(queenPromo);
                            regmove.push_back(knightPromo);
                        }
                    } else if (gameBoard->validmove(team, pos, dest, fake, fake, fake, fake, "DNE")) {
                        // not pawn promotion
                        string move = to_string(i) + to_string(j) + to_string(desti) + to_string(destj) + "DNE";
                        regmove.push_back(move);
                    }
                }
            }
        }
    }

    // return random regmove
    string move = regmove[rand() % (regmove.size())];
    int pos[] = {move[0] - '0', move[1] - '0'};
    int dest[] = {move[2] - '0', move[3] - '0'};
    string promoteType = move.substr(4, -1);
    return gameBoard->moveto(pos, dest, promoteType);
}
