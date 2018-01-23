#ifndef _BLOCK_H_
#define _BLOCK_H_
#include <vector>

class Cell;

//Block class and its subclasses follow factory pattern
class Block{
    //two of the fields are supposedly pointing to nullptr
    int level;
protected:
    std::vector<Cell*> list;
    bool isPartOf(const Cell& cell)const;
    virtual bool canRotate(int isCounter, std::vector<std::vector<Cell>>& grid);
    virtual int rotate(std::vector<std::vector<Cell>>& grid) = 0;
    virtual int crotate(std::vector<std::vector<Cell>>& grid) = 0;
    virtual Block* copy() const= 0;
    virtual Cell* getMinMaxV(int x)const; //if x is 0 return min, else max
    virtual Cell* getMinMaxH(int x)const; //if x is 0 return min, else max
public:
    Cell* getv(int x)const;
    Cell* geth(int x)const;
    Block* copy_wrap()const;
    Block(std::vector<Cell*> lst);
    virtual ~Block(); //block does not own-A cell
    std::vector<Cell*>& getList();
    //remCell is called ONLY if
    //a new block is created or out of booard
    void remCell(Cell* cell); //if success return 1
    bool checkEmpty(int distance, int isDown, const std::vector<std::vector<Cell>>& grid) const;
    //if check the space down isDown is 1, otherwise should give 0
    //if check right distance is positive, else distance is negative
    int go(int distance , std::vector<std::vector<Cell>>& grid);//if success return 1
    int goDown(int distance , std::vector<std::vector<Cell>>& grid);//if success return 1
    int rotate_wrap(std::vector<std::vector<Cell>>& grid);
    int crotate_wrap(std::vector<std::vector<Cell>>& grid);
    void setlevel(int set_level);
    int getlevel();
    
    
    
    
};
#endif

