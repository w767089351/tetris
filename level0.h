//
//  level0.hpp
//  quadris
//
//  Created by Jiayu Shao on 2017-11-27.
//  Copyright © 2017 Jiayu Shao. All rights reserved.
//

#ifndef level0_hpp
#define level0_hpp
#include "nextGenerator.h"
#include <fstream>
#include <iostream>
///////////
//class Block;
//class Cell;
///////////
class Level0:public NextGenerator{
    std::ifstream myfile;
    std::string filename;
    virtual Block* generateNext(std::vector<std::vector <Cell>> &grid,int &success,char &kchar,char &next,bool init,bool norand,std::string norandfilename) override;
public:
    Level0(std::string level0file);
};
#endif /* level0_hpp */

