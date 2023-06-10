#include "textrender.h"
#include "subject.h"
#include "board.h"
#include <iostream>

using namespace std;

TextRender::TextRender(Subject *sub): subject{sub} {
    subject->attach(this);
}


TextRender::~TextRender() {
    subject->detach(this);
}


void TextRender::notify() {
    // Board board = *(subject->getState());
    cout << subject->getState();
}
