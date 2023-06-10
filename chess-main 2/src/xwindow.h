#ifndef XWINDOW_H
#define XWINDOW_H
#include <X11/Xlib.h>
#include <string>

class Xwindow {
    Display *d;
    Window w;
    int s;
    GC gc;
    unsigned long colours[10];

public:
    Xwindow(int width=500, int height=500);  // Constructor; displays the window.
    ~Xwindow();                              // Destructor; destroys the window.
    Xwindow(const Xwindow&) = delete;
    Xwindow &operator=(const Xwindow&) = delete;

    // Available colours.
    enum {White=0, Black, Red, Green, Blue, Cyan, Yellow, Magenta, Orange, Brown};

    // Draws a rectangle
    void fillRectangle(int x, int y, int width, int height, int colour=Black);

    // Draws a string
    void drawString(int x, int y, std::string msg);

    void drawR(int x, int y, int color);
    void drawB(int x, int y, int color);
    void drawN(int x, int y, int color);
    void drawQ(int x, int y, int color);
    void drawK(int x, int y, int color);
    void drawP(int x, int y, int color);
    void drawChessBoard();
    void drawBlackSquare(int x, int y);
    void drawWhiteSquare(int x, int y);
};

#endif
