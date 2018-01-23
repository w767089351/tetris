//
//  nextGenerator.hpp
//  quadris
//
//  Created by Jiayu Shao on 2017-11-27.
//  Copyright © 2017 Jiayu Shao. All rights reserved.
//

#ifndef nextGenerator_hpp
#define nextGenerator_hpp
//#include "block.h"
//#include "cell.h"
//#include "bar.h"
//#include "square.h"
//#include "rect.h"

//////////
#include <vector>
#include <string>

class Block;
class Cell;
///////////
class NextGenerator{
protected:
    virtual Block* generateNext(std::vector<std::vector <Cell>> &grid,int &success,char &k,char &next,bool init,bool norand,std::string norandfilename)=0;
public:
    Block* generate_wrap(std::vector<std::vector <Cell>> &grid,int &success,char &k,char &next,bool init,bool norand,std::string norandfilename);
    //Block* generateBlock(std::vector<std::vector <Cell>> &grid);
    
};
#endif /* nextGenerator_hpp */

