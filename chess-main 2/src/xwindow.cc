#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <unistd.h>
#include "xwindow.h"

using namespace std;

Xwindow::Xwindow(int width, int height) {
    d = XOpenDisplay(NULL);
    if (d == NULL) {
        cerr << "Cannot open display" << endl;
        exit(1);
    }
    s = DefaultScreen(d);
    w = XCreateSimpleWindow(d, RootWindow(d, s), 10, 10, width, height, 1, BlackPixel(d, s), WhitePixel(d, s));
    XSelectInput(d, w, ExposureMask | KeyPressMask);
    XMapRaised(d, w);

    Pixmap pix = XCreatePixmap(d, w, width, height, DefaultDepth(d, DefaultScreen(d)));
    gc = XCreateGC(d, pix, 0,(XGCValues *)0);

    XFlush(d);
    XFlush(d);

    // Set up colours.
    XColor xcolour;
    Colormap cmap;
    char color_vals[10][10]={"white", "black", "red", "green", "blue", "cyan", "yellow", "magenta", "orange", "brown"};

    cmap=DefaultColormap(d,DefaultScreen(d));
    for(int i=0; i < 10; ++i) {
        XParseColor(d,cmap,color_vals[i],&xcolour);
        XAllocColor(d,cmap,&xcolour);
        colours[i]=xcolour.pixel;
    }

    XSetForeground(d,gc,colours[Black]);

    // Make window non-resizeable.
    XSizeHints hints;
    hints.flags = (USPosition | PSize | PMinSize | PMaxSize );
    hints.height = hints.base_height = hints.min_height = hints.max_height = height;
    hints.width = hints.base_width = hints.min_width = hints.max_width = width;
    XSetNormalHints(d, w, &hints);

    XSynchronize(d,True);

    usleep(1000);

    // Make sure we don't race against the Window being shown
    XEvent ev;
    while(1) {
        XNextEvent(d, &ev);
        if(ev.type == Expose) break;
    }
}


Xwindow::~Xwindow() {
    XFreeGC(d, gc);
    XCloseDisplay(d);
}


void Xwindow::fillRectangle(int x, int y, int width, int height, int colour) {
    XSetForeground(d, gc, colours[colour]);
    XFillRectangle(d, w, gc, x, y, width, height);
    XSetForeground(d, gc, colours[Black]);
}


void Xwindow::drawString(int x, int y, string msg) {
    XDrawString(d, w, DefaultGC(d, s), x, y, msg.c_str(), msg.length());
}


void Xwindow::drawR(int x, int y, int color) {
    for(int i = 3; i < 7; ++i) {
        fillRectangle(i*10 + x, 20 + y, 10, 10, color);
    }
    for(int i = 2; i < 9; ++i) {
        fillRectangle(30 + x, i*10 + y, 10, 10, color);
    }
    for(int i = 4; i < 7; ++i) {
        fillRectangle(i * 10 + x, 50 + y, 10, 10, color);
    }
    for(int i = 3; i < 5; ++i) {
        fillRectangle(60 + x, i * 10 + y, 10, 10, color);
    }
    for(int i = 5; i < 8; ++i) {
        fillRectangle(i * 10 + x, (4 + i - 3) * 10 + y, 10, 10, color);
    }
}


void Xwindow::drawB(int x, int y, int color) {
    for(int i = 3; i < 7; ++i) {
        fillRectangle(i*10 + x, 20 + y, 10, 10, color);
    }
    for(int i = 3; i < 7; ++i) {
        fillRectangle(i*10 + x, 50 + y, 10, 10, color);
    }
    for(int i = 3; i < 7; ++i) {
        fillRectangle(i*10 + x, 80 + y, 10, 10, color);
    }
    for(int i = 2; i < 9; ++i) {
        fillRectangle(30 + x, i*10 + y, 10, 10, color);
    }
    for(int i = 3; i < 9; ++i) {
        if ( i != 2 && i != 5 && i != 8) {
            fillRectangle(70 + x, i*10 + y, 10, 10, color);
        }
    }
}


void Xwindow::drawN(int x, int y, int color) {
    for(int i = 2; i < 9; ++i) {
        fillRectangle(30 + x, i*10 + y, 10, 10, color);
    }
    fillRectangle(40 + x, 40 + y, 10, 10, color);
    fillRectangle(50 + x, 50 + y, 10, 10, color);
    fillRectangle(60 + x, 60 + y, 10, 10, color);
    for(int i = 2; i < 9; ++i) {
        fillRectangle(70 + x, i*10 + y, 10, 10, color);
    }
}


void Xwindow::drawQ(int x, int y, int color) {
    for(int i = 3; i < 8; ++i) {
        fillRectangle(30 + x, i*10 + y, 10, 10, color);
    }
    for(int i = 3; i < 8; ++i) {
        fillRectangle(70 + x, i*10 + y, 10, 10, color);
    }
    for(int i = 4; i < 7; ++i) {
        fillRectangle(i*10 + x, 20 + y, 10, 10, color);
    }
    for(int i = 4; i < 7; ++i) {
        fillRectangle(i*10 + x, 80 + y, 10, 10, color);
    }
    fillRectangle(60 + x, 70 + y, 10, 10, color);
    fillRectangle(50 + x, 60 + y, 10, 10, color);
}


void Xwindow::drawK(int x, int y, int color) {
    for(int i = 3; i < 9; ++i) {
        fillRectangle(30 + x, i*10 + y, 10, 10, color);
    }
    fillRectangle(40 + x, 50 + y, 10, 10, color);
    fillRectangle(50 + x, 50 + y, 10, 10, color);
    fillRectangle(50 + x, 50 + y, 10, 10, color);
    fillRectangle(50 + x, 50 + y, 10, 10, color);
    fillRectangle(60 + x, 40 + y, 10, 10, color);
    fillRectangle(60 + x, 60 + y, 10, 10, color);
    fillRectangle(70 + x, 30 + y, 10, 10, color);
    fillRectangle(70 + x, 40 + y, 10, 10, color);
    fillRectangle(70 + x, 70 + y, 10, 10, color);
    fillRectangle(70 + x, 80 + y, 10, 10, color);
}


void Xwindow::drawP(int x, int y, int color) {
    for(int i = 2; i < 9; ++i) {
        fillRectangle(30 + x, i*10 + y, 10, 10, color);
    }
    for(int i = 4; i < 7; ++i) {
        fillRectangle(i*10 + x, 20 + y, 10, 10, color);
    }
    for(int i = 4; i < 7; ++i) {
        fillRectangle(i*10 + x, 50 + y, 10, 10, color);
    }
    fillRectangle(70 + x, 30 + y, 10, 10, color);
    fillRectangle(70 + x, 40 + y, 10, 10, color);
}


void Xwindow::drawBlackSquare(int x, int y) {
    fillRectangle(x, y, 100, 100, Brown);
}


void Xwindow::drawWhiteSquare(int x, int y) {
    fillRectangle(x, y, 100, 100, Orange);
}

void Xwindow::drawChessBoard() {
    string curr = "white";
    string curr_row = "8";
    string curr_col = "a";
    for (int y = 0; y < 8; ++y) {
        for (int x = 0; x < 8; ++x) {
            if (x == 0) {
                drawString( 30, 110 + 100 * y, curr_row);
                curr_row[0] -= 1;
            }
            if (curr == "black") {
                // drawBlackSquare((x+1)*100, (y+1)*100);
                drawBlackSquare(x*100 + 60, y*100 + 60);
            } else {
                // drawWhiteSquare((x+1)*100, (y+1)*100);
                drawWhiteSquare(x*100 + 60, y*100 + 60);
            }
            if (x != 7) {
                curr = curr == "white" ? "black" : "white";
            }
        }
    }
    for (int z = 0; z < 8; ++z) {
        drawString(110 + z * 100, 890, curr_col);
        curr_col[0] += 1;
    }
}



