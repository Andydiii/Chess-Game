#include "chess.h"
#include "textrender.h"
#include "graphicsrender.h"
#include <iostream>

using namespace std;

int main() {
    Chess chess;
    TextRender text {&chess};
    GraphicsRender graphics {&chess};
    // seed random num generation, so rand() won't return same sequence everytime
    srand(time(0));
    while (cin) {
        chess.takeTurn();
    }
    cout << "Final Score:" << endl;
    cout << "White: " << chess.whiteWin << endl;
    cout << "Black: " << chess.blackWin << endl;
}
