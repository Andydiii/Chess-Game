#ifndef OBSERVER_H
#define OBSERVER_H

class Observer {
public:
    virtual ~Observer();
    virtual void notify() = 0;
};

#endif
