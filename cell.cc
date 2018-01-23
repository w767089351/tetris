#include "cell.h"

Cell:: Cell(int r, int c, int s, char k):row(r), col(c), state(s), kind(k){}

void Cell:: changeState(int s){
    if(s==11){
        state = 1;
    }else if(s==10){
        state = 0;
    }
    else if(s == 2){
        if(state==1)state=0;
        else state=1;
    }else if(s == 0) --state;
    else if(s == 1) ++state;
}
void Cell:: changeKind(char k){
    kind = k;
}
int Cell:: getState() const{
    return state;
}
int Cell:: getr() const{
    return row;
}
int Cell:: getc() const{
    return col;
}
char Cell:: getKind() const{
    return kind;
}


