//
//  level4.cpp
//  a5
//
//  Created by 王善澎simida on 2017/11/28.
//  Copyright © 2017年 王善澎. All rights reserved.
//

#include "nextGenerator.h"
#include <iostream>
#include <fstream>
//#include "highLevel.h"
/////////////
//class Cell;
//class Block;
/////////////


class Level3 : public NextGenerator {
    std::ifstream norandfile;
    //bool initrand;
    Block* generateNext(std::vector<std::vector <Cell>> &grid,int &success,char &k,char &next,bool init,bool norand,std::string norandfilename) override;
public:
    //Level3();
};
