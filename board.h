#ifndef _BOARD_H_
#define _BOARD_H_
#include <vector>
#include <iostream>
#include "subject.h"
#include "cell.h"
//#include "graphicDisplay.h"
class Block;
class TextDisplay;
class GraphicsDisplay;
class Record;
class Level0;
class Level1;
class Level2;
class Level3;


class Board: public Subject{
    std::vector<std::vector <Cell>> grid;
    std::vector<Block*> blist;
    TextDisplay* td = nullptr;
    GraphicsDisplay* gd=nullptr;
    Record* record=nullptr;
    Level0* level_0=nullptr;
    Level1* level_1=nullptr;
    Level2* level_2=nullptr;
    Level3* level3_4=nullptr;
    Block* b=nullptr;
    int hiscore;
    char next;
    bool graphics;
    //Record
    //Lower*
    int countFull() const;
    int checkFull() const;//check starting from the bottom left to top right
    //return -1 if the grid currently has no full row
    void setFree(const int freeRow); //set whichever full row to be free
    void remBlock(); //remove whichever block that is useless(all nullptr)
    void addBlock(Block* b);
public:
    Board();
    ~Board();
    void init(std::string level0file,bool graphics);
    int setBlock(const char k,bool init,bool rand,std::string norandfile); //1 if success, 0 end of game
    void move(const int distance, const int isDown);
    //if check the space down isDown is 1, otherwise should give 0
    //if check right distance is positive, else distance is negative
    int drop();//1 if success, 0 end of game
    void rotate(const int isCounter);
    void hint();
    int resetBlock(const char k,bool rand,std::string norandfile);
    void reset(const char k, Block* bp);//reset for hint
    void levelUp();
    void levelDown();
    std::vector<std::vector <Cell>>& getGrid();
    int getlevel();
    char getnext();
    int getscore();
    int gethscore();
    friend std::ostream &operator<<(std::ostream &out, const Board &board);
    //friend class Subject;
    //friend class GraphicsDisplay;
    //friend class GraphicsDisplay;
};
#endif

