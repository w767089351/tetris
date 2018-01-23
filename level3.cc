//
//  level4.cpp
//  a5
//
//  Created by 王善澎simida on 2017/11/28.
//  Copyright © 2017年 王善澎. All rights reserved.
//

#include "level3.h"
///////////
#include "block.h"
#include "cell.h"
#include "bar.h"
#include "square.h"
#include "rect.h"
///////////

Block* Level3::generateNext(std::vector<std::vector <Cell>> &grid,int &success,char &k,char &next,bool init,bool norand,std::string norandfilename) {
    //std::cout<<"level3 is called"<<std::endl;
    
    if(norand==true){
        /**
        if(initrand==true){
            norandfile.open(norandfilename);
            //char nextb;
            norandfile>>k;
            initrand=false;
        }
        **/
        //char nextb;
        norandfile>>next;
        if(norandfile.eof()){
            norandfile.close();
            norandfile.open(norandfilename);
            norandfile>>next;
        }
    }
    
    else if(next=='A'){
        std::cout<<"lalalala"<<std::endl;
        int rand_result=rand() % 9; //range is from 0-8
        //char k;
        if(rand_result==0 || rand_result==1){
            next= 'S';
        }
        else if(rand_result==2 || rand_result== 3){
            next= 'Z';
        }
        else if(rand_result==4){
            next= 'I';
        }
        else if(rand_result==5){
            next= 'J';
        }
        else if(rand_result==6){
            next= 'O';
        }
        else if(rand_result==7){
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
    //b->setlevel(3);
    return b;

}
