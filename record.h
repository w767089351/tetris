#ifndef _RECORD_H_
#define _RECORD_H_
#include <vector>
#include "observer.h"

class Record{
    int level;
    int score;
    int hscore;
    int count;
public:
    Record(int level, int score, int hscore, int count);
    ~Record();
    //void notify(std::vector<std::vector <Cell>>& grid)override;
    int getlevel();
    int getcount();
    int getscore();
    int gethscore();
    void levelup();
    void leveldown();
    void addcount();
    void erasecount();
    void setscore(int gain);
    
};
#endif

