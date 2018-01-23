#ifndef _OBSERVER_H_
#define _OBSERVER_H_
class Subject;
class Cell;
class Board;
class Observer{
public:
    virtual void notify(Board& s)=0;
                        //std::vector<std::vector <Cell>>& grid) = 0;
    virtual ~Observer() = default;
};
#endif


