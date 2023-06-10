#ifndef TEXTRENDER_H
#define TEXTRENDER_H

#include "observer.h"

class Subject;

class TextRender: public Observer{
    Subject *subject;
public:
    TextRender(Subject *sub);
    ~TextRender() override;
    void notify() override;
};

#endif
