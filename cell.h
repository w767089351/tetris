#ifndef _CELL_H_
#define _CELL_H_
class Cell{
    int row;
    int col;
    int state; //0/1 0 refers to unoccupied, 1 refers to occupied
    char kind; //the kind of block, it is in. (7 kinds in total)
public:
    Cell(int r, int c, int s, char k);
    void changeState(int s = 2);
    //if s=2, the state is reversed, s=0, --state
    //s=1,++state      s=11 state=1    s=10 state=0
    void changeKind(char k);
    //by default, it changes from current state to the other
    //elsewise, we can provide 0/1 to customize the state
    //0 refers to deduct 1 from state, and 1 refers add 1 to state
    int getState() const;
    int getr() const;
    int getc() const;
    char getKind() const;
};
#endif


