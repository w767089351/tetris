#ifndef _SQUARE_H_
#define _SQUARE_H_
#include "block.h"

class Square: public Block{
    int rotate(std::vector<std::vector<Cell>>& grid) override;
    int crotate(std::vector<std::vector<Cell>>& grid) override;
    Cell* getMinMaxV(int x)const override; //if x is 0 return min, else max
    Cell* getMinMaxH(int x)const override; //if x is 0 return min, else max
protected:
    Block* copy()const override;
public:
    ~Square();
    Square(std::vector<Cell*> lst);
};
#endif
