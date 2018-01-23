#ifndef _SUBJECT_H_
#define _SUBJECT_H_
#include <vector>
#include "observer.h"
class Board;
class Subject{
protected:
    std::vector<Observer*> observers;
public:
    void attach(Observer* obs);
    void dettach();//detach whatever is nullptr (called by init in board)
    void notifyObservers(Board& s);
};
#endif

