#include "knight.h"
#include "board.h"

using namespace std;

Knight::Knight(int row, int col, string team, bool undercap, bool moved):
    Piece{row, col, team, "knight", undercap, moved, false}
{}


bool Knight::validmove(Board &board, int *dest, bool suicide, bool &canCheck, bool &captureEnemy, bool &escape, bool &canCheckmate, string newType) {
    Piece *destpiece = board.theBoard[dest[0]][dest[1]];
    if (!(0 <= dest[0] && dest[0] < 8 && 0 <= dest[1] && dest[1] < 8) || (destpiece != nullptr && destpiece->getTeam() == team)) {
        // dest is: out of bounds, same team (if dest==pos, team will be same)
        return false;
    }
    // if dest has a piece, then it's guranteed to be different team!!!!!!!!!!

    // check for valid knight squares
    if ((abs(dest[0] - pos[0]) == 2 && abs(dest[1] - pos[1]) == 1) || (abs(dest[0] - pos[0]) == 1 && abs(dest[1] - pos[1]) == 2)) {
        // dest guranteed to be empty OR enemy piece
        if (suicide) {
            // status doesnt matter, since suicide=true only when validmove() is called from 
            return true;
        } else {
            // knight cannot promote
            Board *nb = moveto(board, dest, "DNE");
            bool isUndercheck = nb->check(team);
            string enemy = team == "white" ? "black" : "white";
            canCheck = nb->check(enemy);
            captureEnemy = destpiece != nullptr ? true : false;
            escape = board.theBoard[pos[0]][pos[1]]->getUndercap() && !nb->theBoard[dest[0]][dest[1]]->getUndercap() ? true : false;
            canCheckmate = nb->checkmate(enemy);
            delete nb;
            return !isUndercheck;
        }
    } else {
        // not valid knight move
        return false;
    }
}
