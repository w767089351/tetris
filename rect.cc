#include <vector>
#include "rect.h"
#include "cell.h"

Rect:: Rect(std::vector<Cell*> lst):Block{lst}{}
Rect:: ~Rect(){}
Block* Rect::copy()const{
    return new Rect(list);
}
Cell* Rect:: getMinMaxH(int x)const{
    int max = list[1]->getr();
    int min = list[1]->getr();
    Cell* ma = list[1];
    Cell* mi = list[1];
    for(int i=0; i<list.size();i++){
        if(! list[i])continue;
        if(list[i]->getr()>= max){
            max = list[i]->getr();
            ma = list[i];
        }else if(list[i]->getr()<= min){
            min = list[i]->getr();
            mi = list[i];
        }
    }
    if(x) return ma;
    return mi;
}
Cell* Rect:: getMinMaxV(int x)const{
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
        }else if(list[i]->getc()<=min){
            min = list[i]->getc();
            mi = list[i];
        }
    }
    if(x) return ma;
    return mi;
}
bool Rect:: isHorizontal()const{
    int maxr = getMinMaxH(1)->getr();
    int minr = getMinMaxH(0)->getr();
    if((maxr-minr) == 2) return true;
    return false;
}

int Rect:: rotate(std::vector<std::vector<Cell>>& grid){
    //std::cout<<"heyr"<<std::endl;
    int row = getMinMaxH(1)->getr();
    int col = getMinMaxV(0)->getc();
    int r, c, k;
    if(isHorizontal()&& canRotate(0, grid)){
        for(int i=0; i<list.size(); i++){
            if(!list[i]) continue;
            list[i]->changeState(0);
            r = list[i]->getr();
            c = list[i]->getc();
            k = list[i]->getKind();
            if((r==row)&&(c==col))
                list[i] = &grid[row-1][col];
            else if((r==row-1)&&(c==col))
                list[i] = &grid[row-1][col+1];
            else if((r==row-2)&&(c==col))
                list[i] = &grid[row-1][col+2];
            else if((r==row)&&(c==col+1))
                list[i] = &grid[row][col];
            else if((r==row-1)&&(c==col+1))
                list[i] = &grid[row][col+1];
            else if((r==row-2)&&(c==col+1))
                list[i] = &grid[row][col+2];
            //std::cout<<"3"<<std::endl;
            list[i]->changeState(1);
            list[i]->changeKind(k);
        }
        return 1;
    }else if(canRotate(0, grid)){
        for(int i=0; i<list.size(); i++){
            if(!list[i]) continue;
            list[i]->changeState(0);
            r = list[i]->getr();
            c = list[i]->getc();
            k = list[i]->getKind();
            //std::cout<<"2"<<std::endl;
            if((r==row)&&(c==col))
                list[i] = &grid[row-2][col];
            else if((r==row)&&(c==col+1))
                list[i] = &grid[row-1][col];
            else if((r==row)&&(c==col+2))
                list[i] = &grid[row][col];
            else if((r==row-1)&&(c==col))
                list[i] = &grid[row-2][col+1];
            else if((r==row-1)&&(c==col+1))
                list[i] = &grid[row-1][col+1];
            else if((r==row-1)&&(c==col+2))
                list[i] = &grid[row][col+1];
            //std::cout<<"3"<<std::endl;
            list[i]->changeState(1);
            list[i]->changeKind(k);
        }
        return 1;
    }
    return 0;
}

int Rect:: crotate(std::vector<std::vector<Cell>>& grid){
    //std::cout<<"heyc"<<std::endl;
    int row = getMinMaxH(1)->getr();
    int col = getMinMaxV(0)->getc();
    int r, c, k;
    if(isHorizontal()&& canRotate(1, grid)){
        for(int i=0; i<list.size(); i++){
            if(!list[i]) continue;
            list[i]->changeState(0);
            r = list[i]->getr();
            c = list[i]->getc();
            k = list[i]->getKind();
            //std::cout<<"2"<<std::endl;
            if((r==row)&&(c==col))
                list[i] = &grid[row][col+2];
            else if((r==row-1)&&(c==col))
                list[i] = &grid[row][col+1];
            else if((r==row-2)&&(c==col))
                list[i] = &grid[row][col];
            else if((r==row)&&(c==col+1))
                list[i] = &grid[row-1][col+2];
            else if((r==row-1)&&(c==col+1))
                list[i] = &grid[row-1][col+1];
            else if((r==row-2)&&(c==col+1))
                list[i] = &grid[row-1][col];
            //std::cout<<"3"<<std::endl;
            list[i]->changeState(1);
            list[i]->changeKind(k);
        }
        return 1;
    }else if(canRotate(1, grid)){
        for(int i=0; i<list.size(); i++){
            if(!list[i]) continue;
            list[i]->changeState(0);
            r = list[i]->getr();
            c = list[i]->getc();
            k = list[i]->getKind();
            //std::cout<<"2"<<std::endl;
            if((r==row)&&(c==col))
                list[i] = &grid[row][col+1];
            else if((r==row)&&(c==col+1))
                list[i] = &grid[row-1][col+1];
            else if((r==row)&&(c==col+2))
                list[i] = &grid[row-2][col+1];
            else if((r==row-1)&&(c==col))
                list[i] = &grid[row][col];
            else if((r==row-1)&&(c==col+1))
                list[i] = &grid[row-1][col];
            else if((r==row-1)&&(c==col+2))
                list[i] = &grid[row-2][col];
            //std::cout<<"3"<<std::endl;
            list[i]->changeState(1);
            list[i]->changeKind(k);
        }
        return 1;
    }
    return 0;
}

bool Rect:: canRotate(int isCounter, std::vector<std::vector<Cell>>& grid){
    int row = getMinMaxH(1)->getr();
    int col = getMinMaxV(0)->getc();
    if(isHorizontal()){
        if(isCounter){
            for(int i=0; i<list.size(); i++){
                if(!list[i]) continue;
                int r = list[i]->getr();
                int c = list[i]->getc();
                if((r==row)&&(c==col)&&(grid[row][col+2].getState())
                   &&(!isPartOf(grid[row][col+2])))return false;
                else if((r==row-1)&&(c==col)&&(grid[row][col+1].getState())
                        &&(!isPartOf(grid[row][col+1])))return false;
                else if((r==row-2)&&(c==col)&&(grid[row][col].getState())
                        &&(!isPartOf(grid[row][col])))return false;
                else if((r==row)&&(c==col+1)&&(grid[row-1][col+2].getState())
                        &&(!isPartOf(grid[row-1][col+2])))return false;
                else if((r==row-1)&&(c==col+1)&&(grid[row-1][col+1].getState())
                        &&(!isPartOf(grid[row-1][col+1])))return false;
                else if((r==row-2)&&(c==col+1)&&(grid[row-1][col].getState())
                        &&(!isPartOf(grid[row-1][col])))return false;
                //std::cout<<"row1:"<<row<<"col:"<<col<<std::endl;
            }
        }else{
            for(int i=0; i<list.size(); i++){
                if(!list[i]) continue;
                int r = list[i]->getr();
                int c = list[i]->getc();
                if((r==row)&&(c==col)&&(grid[row-1][col].getState())
                   &&(!isPartOf(grid[row-1][col])))return false;
                else if((r==row-1)&&(c==col)&&(grid[row-1][col+1].getState())
                        &&(!isPartOf(grid[row-1][col+1])))return false;
                else if((r==row-2)&&(c==col)&&(grid[row-1][col+2].getState())
                        &&(!isPartOf(grid[row-1][col+2])))return false;
                else if((r==row)&&(c==col+1)&&(grid[row][col].getState())
                        &&(!isPartOf(grid[row][col])))return false;
                else if((r==row-1)&&(c==col+1)&&(grid[row][col+1].getState())
                        &&(!isPartOf(grid[row][col+1])))return false;
                else if((r==row-2)&&(c==col+1)&&(grid[row][col+2].getState())
                        &&(!isPartOf(grid[row][col+2])))return false;
                //std::cout<<"row2:"<<row<<"col:"<<col<<std::endl;
            }
        }
    }else{
        if(isCounter){
            for(int i=0; i<list.size(); i++){
                if(!list[i]) continue;
                int r = list[i]->getr();
                int c = list[i]->getc();
                if((r==row)&&(c==col)&&(grid[row][col+1].getState())
                   &&(!isPartOf(grid[row][col+1])))return false;
                else if((r==row)&&(c==col+1)&&(grid[row-1][col+1].getState())
                        &&(!isPartOf(grid[row-1][col+1])))return false;
                else if((r==row)&&(c==col+2)&&(grid[row-2][col+1].getState())
                        &&(!isPartOf(grid[row-2][col+1])))return false;
                else if((r==row-1)&&(c==col)&&(grid[row][col].getState())
                        &&(!isPartOf(grid[row][col])))return false;
                else if((r==row-1)&&(c==col+1)&&(grid[row-1][col].getState())
                        &&(!isPartOf(grid[row-1][col])))return false;
                else if((r==row-1)&&(c==col+2)&&(grid[row-2][col].getState())
                        &&(!isPartOf(grid[row-2][col])))return false;
                //std::cout<<"row3:"<<row<<"col:"<<col<<std::endl;
            }
        }else{
            for(int i=0; i<list.size(); i++){
                if(!list[i]) continue;
                int r = list[i]->getr();
                int c = list[i]->getc();
                if((r==row)&&(c==col)&&(grid[row-2][col].getState())
                   &&(!isPartOf(grid[row-2][col])))return false;
                else if((r==row)&&(c==col+1)&&(grid[row-1][col].getState())
                        &&(!isPartOf(grid[row-1][col])))return false;
                else if((r==row)&&(c==col+2)&&(grid[row][col].getState())
                        &&(!isPartOf(grid[row][col])))return false;
                else if((r==row-1)&&(c==col)&&(grid[row-2][col+1].getState())
                        &&(!isPartOf(grid[row-2][col+1])))return false;
                else if((r==row-1)&&(c==col+1)&&(grid[row-1][col+1].getState())
                        &&(!isPartOf(grid[row-1][col+1])))return false;
                else if((r==row-1)&&(c==col+2)&&(grid[row][col+1].getState())
                        &&(!isPartOf(grid[row][col+1])))return false;
                //std::cout<<"row4:"<<row<<"col:"<<col<<std::endl;
            }
        }
    }
    return true;
}

