#ifndef GRAPHICSRENDER_H
#define GRAPHICSRENDER_H

#include "observer.h"
#include "xwindow.h"
#include "board.h"

class Subject;

class GraphicsRender : public Observer {
    Subject *subject;
    Xwindow xwindow;
    Board prevBoard;
    
public:
    GraphicsRender(Subject *sub);
    ~GraphicsRender() override;
    void notify() override;
};
#endif
