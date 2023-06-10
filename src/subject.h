#ifndef SUBJECT_H
#define SUBJECT_H

#include <vector>

class Observer;

class Board;

class Subject {
    std::vector<Observer*> observers;
public:
    virtual ~Subject();
    void attach(Observer* os);
    void detach(Observer* os);
    void notifyObservers();
    virtual Board* getState() = 0;
};

#endif
