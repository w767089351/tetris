#include <vector>
#include "block.h"
#include "cell.h"

Block:: Block(std::vector<Cell*> lst): list{lst},level{0}{}

Block:: ~Block(){}
Cell* Block:: getMinMaxV(int x)const{return nullptr;}
Cell* Block:: getMinMaxH(int x)const{return nullptr;}

Cell* Block:: getv(int x)const{
    return getMinMaxV(x);
}

Cell* Block:: geth(int x)const{
    return getMinMaxH(x);
}

Block* Block:: copy_wrap()const{
    return copy();
}
bool Block:: isPartOf(const Cell& cell)const{
    for(int i=0; i<list.size(); i++){
        if(&cell == list[i]) return true;
    }
    return false;
}

bool Block:: checkEmpty(int distance, int isDown, const std::vector<std::vector<Cell>>& grid)const{
    int r, c, d = distance;
    if(isDown) {//check space below
        for(int i = 0; i<list.size(); i++){
            if(!list[i]) continue;
            r = list[i]->getr() + d;
            c = list[i]->getc();
            if((r<0)||(r>17)||(c<0)||(c>10))return false;
            if(isPartOf(grid[r][c]))continue;
            if(grid[r][c].getState()) return false;
        }
    }else {//check space on the right and left
        for(int i = 0; i<list.size(); i++){
            if(!list[i]) continue;
            r = list[i]->getr();
            c = list[i]->getc() + d;
            if((r<0)||(r>17)||(c<0)||(c>10))return false;
            if(isPartOf(grid[r][c]))continue;
            if(grid[r][c].getState()) return false;
        }
        for(int i = 0; i<list.size(); i++){
            if(!list[i]) continue;
            r = list[i]->getr();
            c = list[i]->getc();
        }
    }
    return true;
}

void Block:: remCell(Cell* cell){
    for(int i = 0; i<list.size(); i++){
        if(list[i] == cell){
            list[i]->changeState(0);
            list[i] = nullptr;
            return;
        }
    }
}

int Block:: go(int distance, std::vector<std::vector<Cell>>& grid){
    int r,c;
    char k;
    if(checkEmpty(distance, 0, grid)){
        for(int i = 0; i<list.size(); i++){
            if(!list[i]) continue;
            list[i]->changeState(0);
            k = list[i]->getKind();
            r = list[i]->getr();
            c = list[i]->getc();
            list[i]=&(grid[r][c + distance]);
            list[i]->changeState(1);
            list[i]->changeKind(k);
        }
        return 1;
    }
    return 0;
}

int Block:: goDown(int distance, std::vector<std::vector<Cell>>& grid){
    int r,c;
    char k;
    if(checkEmpty(distance, 1, grid)){
        for(int i = 0; i<list.size(); i++){
            if(!list[i]) continue;
            list[i]->changeState(0);
            k = list[i]->getKind();
            r = list[i]->getr();
            c = list[i]->getc();
            list[i]=&(grid[r + distance][c]);
            list[i]->changeState(1);
            list[i]->changeKind(k);
        }
        return 1;
    }
    return 0;
}

std::vector<Cell*>& Block:: getList(){
    return list;
}

bool Block:: canRotate(int isCounter, std::vector<std::vector<Cell>>& grid){
    return true;
}
int Block::rotate_wrap(std::vector<std::vector<Cell>>& grid){
    return rotate(grid);
}
int Block::crotate_wrap(std::vector<std::vector<Cell>>& grid){
    return crotate(grid);
}

void Block::setlevel(int set_level){
    level=set_level;
}
int Block::getlevel(){
    return level;
}

