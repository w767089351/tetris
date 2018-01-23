#include "block.h"
#include "unique.h"
#include <vector>

Unique:: Unique(std::vector<Cell*> lst):Block{lst} {}
Unique:: ~Unique(){}
int Unique:: rotate(std::vector<std::vector<Cell>>& grid){return 1;}
int Unique:: crotate(std::vector<std::vector<Cell>>& grid){return 1;}
Block* Unique:: copy()const{
    return new Unique(list);
}
