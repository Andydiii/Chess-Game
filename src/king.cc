#include "king.h"
#include "board.h"

using namespace std;

King::King(int row, int col, string team, bool undercap, bool moved):
    Piece{row, col, team, "king", undercap, moved, false}
{}


bool King::validmove(Board &board, int *dest, bool suicide, bool &canCheck, bool &captureEnemy, bool &escape, bool &canCheckmate, string newType) {
    Piece *destpiece = board.theBoard[dest[0]][dest[1]];
    if (!(0 <= dest[0] && dest[0] < 8 && 0 <= dest[1] && dest[1] < 8) || (destpiece != nullptr && destpiece->getTeam() == team)) {
        // dest is: out of bounds, same team (if dest==pos, team will be same)
        return false;
    }
    // if dest has a piece, then it's guranteed to be different team!!!!!!!!!!    
    
    string enemy = team == "white" ? "black" : "white";

    if (abs(dest[0] - pos[0]) <= 1 && abs(dest[1] - pos[1]) <= 1) {
        // move is within valid range
        if (suicide) {
            // suicide=true only when validmove() is called from King::getUndercheck()
            //      so dest is always the enemy king, so capture enemy always = true (altho this should not be needed at all)
            // also, since we are checking if it's valid to check enemy king, it doesn't matter if
            // this will put our own king in danger, because validmove() is now called from enemy's king
            // SOOOOO as long as move is within valid range, return true 
            return true;
        } else {
            // king cannot promote
            Board *nb = moveto(board, dest, "DNE");
            bool isUndercheck = nb->check(team);
            canCheck = nb->check(enemy);
            captureEnemy = destpiece != nullptr ? true : false;
            escape = board.theBoard[pos[0]][pos[1]]->getUndercap() && !nb->theBoard[dest[0]][dest[1]]->getUndercap() ? true : false;
            canCheckmate = nb->checkmate(enemy);
            delete nb;
            return !isUndercheck;
        }
    } else if (castle(board, dest)) {
        // already checked all needed requirement in castle()
        // for castle, captureEnemy=escape=false
        // but could check/checkmate enemy
        // king cannot promote
        Board *nb = moveto(board, dest, "DNE");
        canCheck = nb->check(enemy);
        captureEnemy = false;
        escape = false;
        canCheckmate = nb->checkmate(enemy);
        delete nb;
        return true;
    }
    return false;
}


bool King::castle(Board &board, int *dest) {
    int row = pos[0];

    if (getMoved() || dest[0] != row || abs(dest[1] - pos[1]) != 2 || getUndercheck(board)) {
        return false;
    }
    // now it's guranteed that king never moved before, dest on same row, col diff by 2, and king not in check at start pos
    if (dest[1] == 2) {
        // left castle
        // [row][0] is allie rook that never moved before
        Piece *leftrook = board.theBoard[row][0];
        if (leftrook != nullptr && leftrook->getTeam() == team && leftrook->getType() == "rook" && !leftrook->getMoved()) {
            // no piece between king and rook
            for (int i = 1; i <= 3; i++) {
                if (board.theBoard[row][i] != nullptr) {
                    return false;
                }
            }
            // make sure king is not in check on middle and end pos
            for (int i = 2; i <= 3; i++) {
                int arr[] = {row, i};
                // king cannot promote, especially since piece::moveto() ignore newType
                Board *nb = Piece::moveto(board, arr, "DNE");
                Piece *king = nb->theBoard[row][i];
                if (king->getUndercheck(*nb)) {
                    delete nb;
                    return false;
                }
                delete nb;
            }
            return true;
        }
    } else {
        // right castle, dest[1] == 6
        // [row][7] is allie rook that never moved before
        Piece *rightrook = board.theBoard[row][7];
        if (rightrook != nullptr && rightrook->getTeam() == team && rightrook->getType() == "rook" && !rightrook->getMoved()) {
            // return false;
            // no piece between king and rook
            // make sure king is not in check on middle and end pos
            for (int i = 5; i <= 6; i++) {
                // no piece in between
                if (board.theBoard[row][i] != nullptr) {
                    return false;
                }
                // not in check
                int arr[] = {row, i};
                // king cannot promote, especially since piece::moveto() ignore newType
                Board *nb = Piece::moveto(board, arr, "DNE");
                Piece *king = nb->theBoard[row][i];
                if (king->getUndercheck(*nb)) {
                    delete nb;
                    return false;
                }
                delete nb;
            }
            return true;
        }
    }
    return false;
}


bool King::getUndercheck(Board &board) {
    // see if king is under check from ANY enemy (go through all 64 pieces)
    // validmove(dest=pos, suicide=true)
    bool fake;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            // suicide = true
            // validmove will make sure [i][j] cant be same team as dest(current king)
            Piece *p = board.theBoard[i][j];
            // cannot use board::validmove cuz it always have suicide=false
            // newType="DNE" cuz suicide=true, so pawn::validmove() will return true
            // before generate newboard with promotion type
            if (p != nullptr && p->getTeam() != team && p->validmove(board, pos, true, fake, fake, fake, fake, "DNE")) {  
                /*
                if king is now black
                then every p enter the condition will be white
                so black king is undercheck as long as white p can move to my pos
                regardless if the move will put white king under check
                AKA suicide=true
                */
                return true;
            }
        }
    }
    return false;
}


Board* King::moveto(Board &board, int *dest, string newType) {
    // king cannot promote, moreover, piece::moveto() ignore newType
    Board *nb = Piece::moveto(board, dest, "DNE");
    if (castle(board, dest)) {
        int row = pos[0];
        // move rook, set rook's moved status to true, or simply using piece::moveto()
        if (dest[1] == 2) {
            // left castle
            Piece *leftrook = nb->theBoard[row][0];
            int arr[] = {row, 3};
            // rook cannot promote
            Board *nnb = leftrook->moveto(*nb, arr, "DNE");
            delete nb;
            nb = nnb;
        } else {
            // right castle
            Piece *rightrook = nb->theBoard[row][7];
            int arr[] = {row, 5};
            // rook cannot promote
            Board *nnb = rightrook->moveto(*nb, arr, "DNE");
            delete nb;
            nb = nnb;
        }
    }
    return nb;
}
