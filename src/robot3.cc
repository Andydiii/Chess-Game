#include "robot3.h"
#include "board.h"
#include "piece.h"
#include <vector>

using namespace std;

Robot3::Robot3(string team):
    Player{team}
{}


Board* Robot3::move(Board* gameBoard, bool &success) {
    // robot will always have a valid move
    success = true;
    vector<string> alphamove;
    vector<string> regmove;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            int pos[] = {i, j};
            for (int desti = 0; desti < 8; desti++) {
                for (int destj = 0; destj < 8; destj++) {
                    
                    int dest[] = {desti, destj};
                    Piece *p = gameBoard->theBoard[i][j];
                    bool canCheck, canCapture, canEscape, fake;
                    
                    if (p != nullptr && p->getType() == "pawn" && (desti == 0 || desti == 7)) {
                        // pawn promotion
                        if (gameBoard->validmove(team, pos, dest, canCheck, canCapture, canEscape, fake, "queen")) {
                            string queenPromo = to_string(i) + to_string(j) + to_string(desti) + to_string(destj) + "queen";
                            if (canCapture || canEscape || canCheck) {
                                alphamove.push_back(queenPromo);
                            } else {
                                regmove.push_back(queenPromo);
                            }
                        }
                        if (gameBoard->validmove(team, pos, dest, canCheck, canCapture, canEscape, fake, "knight")) {
                            string knightPromo = to_string(i) + to_string(j) + to_string(desti) + to_string(destj) + "knight";
                            if (canCapture || canEscape || canCheck) {
                                alphamove.push_back(knightPromo);
                            } else {
                                regmove.push_back(knightPromo);
                            }
                        }
                    } else if (gameBoard->validmove(team, pos, dest, canCheck, canCapture, canEscape, fake, "DNE")) {
                        // not pawn promotion
                        string move = to_string(i) + to_string(j) + to_string(desti) + to_string(destj) + "DNE";
                        if (canCapture || canEscape || canCheck) {
                            alphamove.push_back(move);
                        } else {
                            regmove.push_back(move);
                        }
                    }
                }
            }
        }
    }

    if (alphamove.size() > 0) {
        // choose random alphamove
        string move = alphamove[rand() % (alphamove.size())];
        int pos[] = {move[0] - '0', move[1] - '0'};
        int dest[] = {move[2] - '0', move[3] - '0'};
        string promoteType = move.substr(4, -1);
        return gameBoard->moveto(pos, dest, promoteType);
    } else {
        // choose random regmove
        string move = regmove[rand() % (regmove.size())];
        int pos[] = {move[0] - '0', move[1] - '0'};
        int dest[] = {move[2] - '0', move[3] - '0'};
        string promoteType = move.substr(4, -1);
        return gameBoard->moveto(pos, dest, promoteType);
    }
}
