#include "graphicsrender.h"
#include "subject.h"
#include "xwindow.h"
#include "board.h"
#include "piece.h"
#include <string>

using namespace std;

GraphicsRender::GraphicsRender(Subject *sub):
    subject{sub}, xwindow{925, 925}, prevBoard{true}
{
    subject->attach(this);
    // draw empty board, same as prev board
    xwindow.drawChessBoard();
}


GraphicsRender::~GraphicsRender() {
    subject->detach(this);
}


void GraphicsRender::notify() {
    Board *board = subject->getState();
    for (int i = 7; i >= 0; i--) {  
        for (int j = 0; j < 8; j++) {
            Piece *p = board->theBoard[i][j];
            Piece *prevP = prevBoard.theBoard[i][j];
            
            if ((p == nullptr && prevP == nullptr) || 
            (p != nullptr && prevP != nullptr && p->getType() == prevP->getType() && p->getTeam() == prevP->getTeam())) {
                continue;
            }
            // empty -> piece   dont need to paint background
            // piece -> empty   paint background
            // piece -> piece   paitn background
            int x = j * 100 + 60;
            int y = (7 - i) * 100 + 60;
            if (prevP != nullptr) {
                if (i % 2 == j % 2) {
                    // i,j both odd/even -> black square
                    xwindow.drawBlackSquare(x, y);
                } else {
                    xwindow.drawWhiteSquare(x, y);
                }
            }
            // when reach here, we have pure background
            if (p == nullptr) {
                continue;
            }
            
            string type = p->getType();
            int color = p->getTeam() == "white" ? xwindow.White : xwindow.Black;
            
            if (type == "rook") {
                xwindow.drawR(x, y, color);
            } else if (type == "bishop") {
                xwindow.drawB(x, y, color);
            } else if (type == "knight") {
                xwindow.drawN(x, y, color);
            } else if (type == "queen") {
                xwindow.drawQ(x, y, color);
            } else if (type == "king") {
                xwindow.drawK(x, y, color);
            } else if (type == "pawn") {
                xwindow.drawP(x, y, color);
            }
        }
    }
    prevBoard = Board {*board};
}
