#include "block.h"
#include "square.h"
#include "cell.h"
#include <vector>


Square:: Square(std::vector<Cell*> lst):Block{lst} {}
Square::~Square(){}
int Square:: rotate(std::vector<std::vector<Cell>>& grid){return 1;}
int Square:: crotate(std::vector<std::vector<Cell>>& grid){return 1;}

Block* Square::copy()const{
    return new Square(list);
}

Cell* Square:: getMinMaxH(int x)const{
    int max = list[1]->getr();
    int min = list[1]->getr();
    Cell* ma = list[1];
    Cell* mi = list[1];
    for(int i=0; i<list.size();i++){
        if(! list[i])continue;
        if(list[i]->getr()>= max){
            max = list[i]->getr();
            ma = list[i];
        }else if(list[i]->getr()<= min) {
            min = list[i]->getr();
            mi = list[i];
        }
    }
    if(x) return ma;
    return mi;
}
Cell* Square:: getMinMaxV(int x)const{
    int max = list[1]->getc();
    int min = list[1]->getc();
    Cell* ma = list[1];
    Cell* mi = list[1];
    for(int i=0; i<list.size();i++){
        //std::cout<<"2"<<std::endl;
        if(! list[i])continue;
        if(list[i]->getc()>=max){
            max = list[i]->getc();
            ma = list[i];
        }else if(list[i]->getc()<= min){
            min = list[i]->getc();
            mi = list[i];
        }
    }
    if(x) return ma;
    return mi;
}
