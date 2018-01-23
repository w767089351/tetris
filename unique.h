#ifndef _UNIQUE_H_
#define _UNIQUE_H_
#include "unique.h"

class Unique: public Block{
    int rotate(std::vector<std::vector<Cell>>& grid) override;
    int crotate(std::vector<std::vector<Cell>>& grid) override;
protected:
    Block* copy()const override;
public:
    ~Unique();
    Unique(std::vector<Cell*> lst);
};
#endif
