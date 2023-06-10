#include "pawn.h"
#include "board.h"
#include "rook.h"
#include "queen.h"
#include "bishop.h"
#include "knight.h"

using namespace std;

Pawn::Pawn(int row, int col, string team, bool undercap, bool moved, bool canEnpassant):
    Piece{row, col, team, "pawn", undercap, moved, canEnpassant}
{}


// CHECK FOR ENPASSANT
bool Pawn::validmove(Board &board, int *dest, bool suicide, bool &canCheck, bool &captureEnemy, bool &escape, bool &canCheckmate, string newType) {
    Piece *destpiece = board.theBoard[dest[0]][dest[1]];
    if (!(0 <= dest[0] && dest[0] < 8 && 0 <= dest[1] && dest[1] < 8) || (destpiece != nullptr && destpiece->getTeam() == team)) {
        // dest is: out of bounds, same team (if dest==pos, team will be same)
        return false;
    }
    // if dest has a piece, then it's guranteed to be different team!!!!!!!!!!
    
    bool valid = false;

    // regular moves
    if (team == "white") {
        // white can only go up
        if (dest[0] == pos[0] + 1 && abs(dest[1] - pos[1]) == 1 && destpiece != nullptr) {
            // overtake up diagonal by 1
            valid = true;
        } else if (dest[0] == pos[0] + 1 && dest[1] == pos[1] && destpiece == nullptr) {
            // move up by 1
            valid = true;
        } else if (pos[0] == 1 && dest[0] == 3 && dest[1] == pos[1] && destpiece == nullptr && board.theBoard[2][pos[1]] == nullptr) {
            // white pawn is making first move, attempt to go up by 2 to row 3
            // check that up_by_1 (row 2) AND up_by_2 (row 3, dest) are both empty
            valid = true;
        }
    } else {
        // team == "black"
        // black can only go down
        if (dest[0] == pos[0] - 1 && abs(dest[1] - pos[1]) == 1 && destpiece != nullptr) {
            // overtake down diagonal by 1
            valid = true;
        } else if (dest[0] == pos[0] - 1 && dest[1] == pos[1] && destpiece == nullptr) {
            // move down by 1
            valid = true;
        } else if (pos[0] == 6 && dest[0] == 4 && dest[1] == pos[1] && destpiece == nullptr && board.theBoard[5][pos[1]] == nullptr) {
            // black pawn is making first move, attempt to go down by 2 to row 4
            // check that down_by_1 (row 5) AND down_by_2 (row 4, dest) are both empty
            valid = true;
        }
    }

    if (enpassant(board, dest)) {
        valid = true;
    }

    if (!valid) {
        return false;
    }

    if (suicide) {
        // status doesnt matter, since suicide=true only when validmove() is called from 
        return true;
    } else {
        // pawn can promote
        Board *nb = moveto(board, dest, newType);
        bool isUndercheck = nb->check(team);
        string enemy = team == "white" ? "black" : "white";
        canCheck = nb->check(enemy);
        captureEnemy = destpiece != nullptr ? true : false;
        escape = board.theBoard[pos[0]][pos[1]]->getUndercap() && !nb->theBoard[dest[0]][dest[1]]->getUndercap() ? true : false;
        canCheckmate = nb->checkmate(enemy);
        delete nb;
        return !isUndercheck;
    }
}


bool Pawn::enpassant(Board &board, int *dest) {
    Piece *destpiece = board.theBoard[dest[0]][dest[1]];
    // for enpassant, dest has to be empty and cur_piece is moving forward diagonal by 1
    if (destpiece == nullptr && abs(dest[1] - pos[1]) == 1 && ((team == "white" && dest[0] == pos[0] + 1) || (team == "black" && dest[0] == pos[0] - 1))) {   
        // now check enemy pawn with enpassant activated is on the same row as pos, and same col as dest
        Piece *p = board.theBoard[pos[0]][dest[1]];
        if (p != nullptr && p->getTeam() != team && p->getType() == "pawn" && p->getEnpassant()) {
            return true;
        }
    }
    return false;
}


Board* Pawn::moveto(Board &board, int *dest, string newType) {
    // piece::moveto() ignore newType, pawn promotion will be handled separately bellow
    // piece::moveto() only update pos & undercap for new piece
    Board *nb = Piece::moveto(board, dest, "DNE");
    if (!getMoved() && abs(dest[0] - pos[0]) == 2) {
        // first move by 2, trigger enpassant
        nb->theBoard[dest[0]][dest[1]]->setEnpassant(true);
    } else if (enpassant(board, dest)) {
        // free piece at same row as pos, and same col as dest
        delete nb->theBoard[pos[0]][dest[1]];
        nb->theBoard[pos[0]][dest[1]] = nullptr;
    }
    
    // pawn promotion
    if (dest[0] == 0 || dest[0] == 7) {
        // pawn reach first or last row, change to newType
        bool cap = nb->theBoard[dest[0]][dest[1]];
        delete nb->theBoard[dest[0]][dest[1]];
        if (newType == "rook") {
            nb->theBoard[dest[0]][dest[1]] = new Rook(dest[0], dest[1], team, cap, true);
        } else if (newType == "knight") {
            nb->theBoard[dest[0]][dest[1]] = new Knight(dest[0], dest[1], team, cap, true);
        } else if (newType == "bishop") {
            nb->theBoard[dest[0]][dest[1]] = new Bishop(dest[0], dest[1], team, cap, true);
        } else if (newType == "queen") {
            nb->theBoard[dest[0]][dest[1]] = new Queen(dest[0], dest[1], team, cap, true);
        } else {
            throw "Board::moveto() recieved unknown newType!!!!!!!!!!!!!!!";
        }
    }
    
    return nb;
}
