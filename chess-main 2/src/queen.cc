#include "queen.h"
#include "board.h"

using namespace std;

Queen::Queen(int row, int col, string team, bool undercap, bool moved):
    Piece{row, col, team, "queen", undercap, moved, false}
{}


bool Queen::validmove(Board &board, int *dest, bool suicide, bool &canCheck, bool &captureEnemy, bool &escape, bool &canCheckmate, string newType) {
    Piece *destpiece = board.theBoard[dest[0]][dest[1]];
    if (!(0 <= dest[0] && dest[0] < 8 && 0 <= dest[1] && dest[1] < 8) || (destpiece != nullptr && destpiece->getTeam() == team)) {
        // dest is: out of bounds, same team (if dest==pos, team will be same)
        return false;
    }
    // if dest has a piece, then it's guranteed to be different team!!!!!!!!!!

    // check for rook like move (straight line)
    // check that all middle pieces (except start and dest) are nullptrs
    if (dest[0] == pos[0] && dest[1] > pos[1]) {
        // go right
        int i = pos[0];
        for (int j = pos[1]+1; j < dest[1]; j++) {
            if (board.theBoard[i][j] != nullptr) {
                return false;
            }
        }
    } else if (dest[0] == pos[0] && dest[1] < pos[1]) {
        // go left
        int i = pos[0];
        for (int j = pos[1]-1; j > dest[1]; j--) {
            if (board.theBoard[i][j] != nullptr) {
                return false;
            }
        }
    } else if (dest[0] > pos[0] && dest[1] == pos[1]) {
        // go up
        int j = pos[1];
        for (int i = pos[0]+1; i < dest[0]; i++) {
            if (board.theBoard[i][j] != nullptr) {
                return false;
            }
        }
    } else if (dest[0] < pos[0] && dest[1] == pos[1]) {
        // go down
        int j = pos[1];
        for (int i = pos[0]-1; i > dest[0]; i--) {
            if (board.theBoard[i][j] != nullptr) {
                return false;
            }
        }

    } else if (abs((dest[0] - pos[0])) == abs((dest[1] - pos[1]))) {
        // check for bishop like move (diagonal)
        // check that all pieces in the middle (except start and dest) are nullptrs

        // gap > 0 gurantee, if gap==0, then dest.team==cur.team would return false at start
        int gap = abs(dest[0] - pos[0]);

        if ((dest[0] > pos[0]) && (dest[1] > pos[1])) {
            // diagonal up right
            for (int i = 1; i < gap; i++) {
                if (board.theBoard[pos[0] + i][pos[1] + i] != nullptr) {
                    return false;
                }
            }
        } else if ((dest[0] > pos[0]) && (dest[1] < pos[1])) {
            // diagonal up left
            for (int i = 1; i < gap; i++) {
                if (board.theBoard[pos[0] + i][pos[1] - i] != nullptr) {
                    return false;
                }
            }
        } else if ((dest[0] < pos[0]) && (dest[1] > pos[1])) {
            // diagonal down right
            for (int i = 1; i < gap; i++) {
                if (board.theBoard[pos[0] - i][pos[1] + i] != nullptr) {
                    return false;
                }
            }
        } else {
            // diagonal down left
            for (int i = 1; i < gap; i++) {
                if (board.theBoard[pos[0] - i][pos[1] - i] != nullptr) {
                    return false;
                }
            }
        }
    } else {
        // not straight and not diagonal
        return false;
    }

    if (suicide) {
        // status doesnt matter, since suicide=true only when validmove() is called from 
        return true;
    } else {
        // queen cannot promote
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
}
