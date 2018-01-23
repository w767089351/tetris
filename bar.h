#ifndef _BAR_H_
#define _BAR_H_
#include "block.h"

class Bar: public Block {
    bool isHorizontal()const;
    Cell* getMinMaxV(int x)const override; //if x is 0 return min, else max
    Cell* getMinMaxH(int x)const override; //if x is 0 return min, else max
    bool canRotate(int isCounter, std::vector<std::vector<Cell>>& grid) override;
    int rotate(std::vector<std::vector<Cell>>& grid) override;
    int crotate(std::vector<std::vector<Cell>>& grid) override;
protected:
    Block* copy()const override;
public:
    Bar(std::vector<Cell*> lst);
    ~Bar();
    
    
};
#endif

