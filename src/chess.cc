#include "chess.h"
#include "board.h"
#include "piece.h"
#include "rook.h"
#include "bishop.h"
#include "knight.h"
#include "queen.h"
#include "king.h"
#include "pawn.h"
#include "player.h"
#include "human.h"
#include "robot1.h"
#include "robot2.h"
#include "robot3.h"
#include "robot4.h"
#include <iostream>

using namespace std;

Chess::Chess():
    gameStart{false}, curBoard{nullptr}, prevBoard{nullptr}, white{nullptr}, black{nullptr}, whiteWin{0}, blackWin{0}
{}


Chess::~Chess() {
    delete curBoard;
    delete prevBoard;
    delete white;
    delete black;
}


void Chess::takeTurn() {
    string command;
    while (cin >> command) {
        if (command == "game") {
            if (gameStart) {
                cout << "invalid command, game in progress" << endl;
                continue;
            }

            string whiteP, blackP;
            cin >> whiteP >> blackP;

            if ((whiteP == "human" || whiteP == "robot1" || whiteP == "robot2" || whiteP == "robot3" || whiteP == "robot4") && 
            (blackP == "human" || blackP == "robot1" || blackP == "robot2" || blackP == "robot3" || blackP == "robot4")) {
                gameStart = true;
                gameRunning = false;

                delete prevBoard;
                delete curBoard;
                delete white;
                delete black;
                prevBoard = nullptr;
                curBoard = new Board {};
                
                curPlayer = "white";
                
                if (whiteP == "human") {
                    white = new Human{"white"};
                } else if (whiteP == "robot1") {
                    white = new Robot1{"white"};
                } else if (whiteP == "robot2") {
                    white = new Robot2{"white"};
                } else if (whiteP == "robot3") {
                    white = new Robot3{"white"};
                } else {
                    white = new Robot4{"white"};
                }

                if (blackP == "human") {
                    black = new Human{"black"};
                } else if (blackP == "robot1") {
                    black = new Robot1{"black"};
                } else if (blackP == "robot2") {
                    black = new Robot2{"black"};
                } else if (blackP == "robot3") {
                    black = new Robot3{"black"};
                } else {
                    black = new Robot4{"black"};
                }
                
                notifyObservers();
            } else {
                cout << "invalid command, unknown player type" << endl;
            }
        // end of "game"

        } else if (command == "resign") {
            if (!gameStart) {
                cout << "invalid command, no game in progress" << endl;
            }
            
            if (curPlayer == "white") {
                blackWin++;
                cout << "Black wins!" << endl;
            } else {
                whiteWin++;
                cout << "White wins!" << endl;
            }
            
            reset();
        // end of "resign"

        } else if (command == "move") {
            if (!gameStart) {
                cout << "invalid command, cannot move when game is not running" << endl;
                continue;
            }

            bool success;
            Board *tmpBoard;

            if (curPlayer == "white") {
                tmpBoard = white->move(curBoard, success);
            } else {
                tmpBoard = black->move(curBoard, success);
            }

            if (!success) {
                // no error message needed, human::move will display error message, robot::move will always be sucess=true
                continue;
            }
            
            gameRunning = true;
            
            delete prevBoard;
            prevBoard = curBoard;
            curBoard = tmpBoard;

            // switch player
            curPlayer = curPlayer == "white" ? "black" : "white";
            // notify observers after move
            notifyObservers();
            bool terminate = false;

            if (curBoard->checkmate("black")) {
                cout << "Checkmate! White wins!" << endl;
                whiteWin++;
                terminate = true;
            } else if (curBoard->checkmate("white")) {
                cout << "Checkmate! Black wins!" << endl;
                blackWin++;
                terminate = true;
            } else if (curBoard->check("black")) {
                cout << "Black is in check." << endl;
            } else if (curBoard->check("white")) {
                cout << "White is in check." << endl;
            } else if ((curPlayer == "black" && curBoard->stalemate("black")) || (curPlayer == "white" && curBoard->stalemate("white"))) {
                cout << "Stalemate!" << endl;
                whiteWin += 0.5;
                blackWin += 0.5;
                terminate = true;
            } else if (curBoard->twoKing()) {
                cout << "Draw!" << endl;
                whiteWin += 0.5;
                blackWin += 0.5;
                terminate = true;
            }

            if (terminate) {
                reset();
            }
        // end of "move"

        } else if (command == "setup") {
            if ((gameStart == true) && (gameRunning == false)) {
                string pos;
                char type;
                int row;
                int col;

                while (cin >> command) {
                    if (command == "+") {
                        cin >> type >> pos;
                        if ('a' <= pos[0] && pos[0] <= 'h' && '1' <= pos[1] && pos[1] <= '8') {
                            row = pos[1] - '1';
                            col = pos[0] - 'a';
                            Piece *oldp = curBoard->theBoard[row][col];
                            // pointer to [row][col]
                            Piece **p = &curBoard->theBoard[row][col];

                            if (type == 'K') {
                                *p = new King(row, col, "white", false, false);
                            } else if (type == 'Q') {
                                *p = new Queen(row, col, "white", false, false);
                            } else if (type == 'R') {
                                *p = new Rook(row, col, "white", false, false);
                            } else if (type == 'B') {
                                *p = new Bishop(row, col, "white", false, false);
                            } else if (type == 'N') {
                                *p = new Knight(row, col, "white", false, false);
                            } else if (type == 'P') {
                                *p = new Pawn(row, col, "white", false, false, false);
                            } else if (type == 'k') {
                                *p = new King(row, col, "black", false, false);
                            } else if (type == 'q') {
                                *p = new Queen(row, col, "black", false, false);
                            } else if (type == 'r') {
                                *p = new Rook(row, col, "black", false, false);
                            } else if (type == 'b') {
                                *p = new Bishop(row, col, "black", false, false);
                            } else if (type == 'n') {
                                *p = new Knight(row, col, "black", false, false);
                            } else if (type == 'p') {
                                *p = new Pawn(row, col, "black", false, false, false);
                            } else {
                                cout << "invalid command, unknown type" << endl;
                                // put oldp back to board
                                *p = oldp;
                                continue;
                            }
                            // free oldp here, after knowing type is valid
                            delete oldp;
                            // notify observers after sucess "+"
                            notifyObservers();
                        } else {
                            cout << "invalid command, pos is out of range" << endl;
                        }
                    // end of "+"

                    } else if (command == "-") {
                        cin >> pos;
                        if ('a' <= pos[0] && pos[0] <= 'h' && '1' <= pos[1] && pos[1] <= '8') {
                            row = pos[1] - '1';
                            col = pos[0] - 'a';
                            // [row][col] is either Piece or nullptr, delete is fine eitherway
                            delete curBoard->theBoard[row][col];
                            curBoard->theBoard[row][col] = nullptr;
                            notifyObservers();
                        } else {
                            cout << "invalid command, move is out of range" << endl;
                        }
                    // end of "-"

                    } else if (command == "=") {
                        string team;
                        cin >> team;
                        if (team == "white" || team == "black") {
                            curPlayer = team;
                        } else {
                            cout << "invalid command, unknown colour" << endl;
                        }
                    // end of "="
                    
                    } else if (command == "done") {
                        // check for validboard after setup is compelete
                        if (!(curBoard->validBoard())) {
                            cout << "invalid board" << endl;
                            continue;
                        }

                        notifyObservers();
                        // update undercap status for 
                        curBoard->setUndercap();
                        // upon leaving setup mode, set all piece moved to be true, AKA disable castle and enpassant
                        for (int i = 0; i < 8; i++) {
                            for (int j = 0; j < 8; j++) {
                                Piece *p = curBoard->theBoard[i][j];
                                if (p == nullptr) {
                                    continue;
                                }
                                p->setMoved(true);
                            }
                        }
                        // if board is stalemate on current team, output message, increase win count, playing = false
                        if (curBoard->stalemate(curPlayer)) {
                            cout << "Stalemate!" << endl;
                            whiteWin += 0.5;
                            blackWin += 0.5;
                            reset();
                        } else if (curBoard->twoKing()) {
                            cout << "Draw!" << endl;
                            whiteWin += 0.5;
                            blackWin += 0.5;
                            reset();
                        }
                        break;
                    // end of "done"
                    } else if (command == "blank") {
                        // graphic.prev == chess.cur
                        delete curBoard;
                        // delete graphive.prev, graphics.prev still == chess.cur, and dereference it is now undefined behaviour, cuz its freed already
                        curBoard = new Board {true};
                        // finally, graphics.prev != chess.cur, but graphics.prev still has undfined dereference behaviour
                        notifyObservers();
                    } else {
                        cout << "invalid command, unknown setup command" << endl;
                    }
                // end of "setup command loop"
                }
            } else {
                cout << "invalid command, cannot enter set-up mode when a game is in progress" << endl;   
                continue;
            }
        // end of "setup"

        } else if (command == "undo") {
            // check if game is running
            if (gameRunning) {
                if (prevBoard != nullptr) {
                    curPlayer = curPlayer == "white" ? "black" : "white";
                    delete curBoard;
                    curBoard = prevBoard;
                    prevBoard = nullptr;
                    notifyObservers();
                } else {
                    cout << "invalid command. No prior move exists" << endl;
                }
            } else {
                cout << "invalid command. No game is currenting running" << endl;
            }
        } else {
            cout << "invalid command, not a valid command type" << endl;
        }
    }
}


Board* Chess::getState() {
    return curBoard;
}


void Chess::reset() {
    gameRunning = false;
    gameStart = false;
    delete curBoard;
    delete prevBoard;
    delete white;
    delete black;
    curBoard = nullptr;
    prevBoard = nullptr;
    white = nullptr;
    black = nullptr;
    cout << "\n=======================\n" << endl;
}
