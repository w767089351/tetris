#ifndef _RECT_H_
#define _RECT_H_
#include "block.h"

class Rect: public Block{
    bool isHorizontal()const;
    //the following two only get from the left side
    Cell* getMinMaxV(int x)const override; //if x is 0 return min, else max
    Cell* getMinMaxH(int x)const override; //if x is 0 return min, else max
    bool canRotate(int isCounter, std::vector<std::vector<Cell>>& grid) override;
    //isCounter=1 crotate, isCounter=0 rotate,
    int rotate(std::vector<std::vector<Cell>>& grid) override;
    int crotate(std::vector<std::vector<Cell>>& grid) override;
protected:
    Block* copy()const override;
public:
    Rect(std::vector<Cell*> lst);
    ~Rect();
    
};
#endif
