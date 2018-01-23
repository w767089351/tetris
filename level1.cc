//
//  level1.cpp
//  quadris
//
//  Created by Jiayu Shao on 2017-11-27.
//  Copyright © 2017 Jiayu Shao. All rights reserved.
//

//#include <ctime>
#include "level1.h"
///////////
#include "block.h"
#include "cell.h"
#include "bar.h"
#include "square.h"
#include "rect.h"
///////////

Block* Level1::generateNext(std::vector<std::vector <Cell>> &grid,int &success,char &k,char &next,bool init,bool norand,std::string norandfilename){
    //std::cout<<"level1 is called"<<std::endl;
    //char k;
    //srand(Null);
    if(next=='A'){
        rand_result=rand() % 12; //range is from 0-11
        if(rand_result== 0){
            next= 'S';
        }
        else if(rand_result==1){
            next= 'Z';
        }
        else if(rand_result==2||rand_result==3){
            next= 'I';
        }
        else if(rand_result==4||rand_result==5){
            next= 'J';
        }
        else if(rand_result==6||rand_result==7){
            next= 'O';
        }
        else if(rand_result==8||rand_result==9){
            next= 'T';
        }
        else{
            next= 'L';
        }
    }
    else{
        char swp;
        swp=next;
        next=k;
        k=swp;
    }
    std::vector<Cell*> lst;
    if(k == 'I'){
        if(grid[3][0].getState()||grid[3][1].getState()||
           grid[3][2].getState()||grid[3][3].getState()){
            success= 0;
        }
        lst.emplace_back(&grid[0][0]);
        lst.emplace_back(&grid[0][1]);
        lst.emplace_back(&grid[0][2]);
        lst.emplace_back(&grid[0][3]);
    }else if(k=='O'){
        if(grid[3][0].getState()||grid[3][1].getState()||
           grid[4][0].getState()||grid[4][1].getState())
            success= 0;
        lst.emplace_back(&grid[0][0]);
        lst.emplace_back(&grid[0][1]);
        lst.emplace_back(&grid[1][0]);
        lst.emplace_back(&grid[1][1]);
    }else if(k == 'J'){
        if(grid[3][0].getState()||grid[4][0].getState()||
           grid[4][1].getState()||grid[4][2].getState())
            success= 0;
        lst.emplace_back(&grid[0][0]);
        lst.emplace_back(&grid[1][0]);
        lst.emplace_back(&grid[1][1]);
        lst.emplace_back(&grid[1][2]);
    }else if(k == 'L'){
        if(grid[4][0].getState()||grid[4][1].getState()||
           grid[4][2].getState()||grid[3][2].getState())
            success= 0;
        lst.emplace_back(&grid[1][0]);
        lst.emplace_back(&grid[1][1]);
        lst.emplace_back(&grid[1][2]);
        lst.emplace_back(&grid[0][2]);
    }else if(k == 'S'){
        if(grid[3][1].getState()||grid[3][2].getState()||
           grid[4][0].getState()||grid[4][1].getState())
            success= 0;
        lst.emplace_back(&grid[0][1]);
        lst.emplace_back(&grid[0][2]);
        lst.emplace_back(&grid[1][0]);
        lst.emplace_back(&grid[1][1]);
    }else if(k == 'Z'){
        if(grid[3][0].getState()||grid[3][1].getState()||
           grid[4][1].getState()||grid[4][2].getState())
            success= 0;
        lst.emplace_back(&grid[0][0]);
        lst.emplace_back(&grid[0][1]);
        lst.emplace_back(&grid[1][1]);
        lst.emplace_back(&grid[1][2]);
    }else if(k == 'T'){
        if(grid[3][0].getState()||grid[3][1].getState()||
           grid[3][2].getState()||grid[4][1].getState())
            success= 0;
        lst.emplace_back(&grid[0][0]);
        lst.emplace_back(&grid[0][1]);
        lst.emplace_back(&grid[0][2]);
        lst.emplace_back(&grid[1][1]);
    }
    lst.emplace_back(nullptr);
    lst.emplace_back(nullptr);
    lst[0]->changeKind(k);
    lst[1]->changeKind(k);
    lst[2]->changeKind(k);
    lst[3]->changeKind(k);
    lst[0]->changeState(1);
    lst[1]->changeState(1);
    lst[2]->changeState(1);
    lst[3]->changeState(1);
    Block*b;
    if(k == 'I') b = new Bar(lst);
    else if(k == 'O')  b = new Square(lst);
    else  b = new Rect(lst);
    //b->setlevel(1);
    return b;
}
