//
//  nextGenerator.cpp
//  quadris
//
//  Created by Jiayu Shao on 2017-11-27.
//  Copyright © 2017 Jiayu Shao. All rights reserved.
//

#include "nextGenerator.h"
///////////
#include "block.h"
#include "cell.h"

///////////


Block* NextGenerator::generate_wrap(std::vector<std::vector <Cell>> &grid,int &success,char &k,char &next,bool init,bool norand,std::string norandfilename){
    return generateNext(grid,success,k,next,init,norand,norandfilename);
}

