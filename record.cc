#include "record.h"

Record:: Record(int level, int score, int hscore, int count):
level{level}, score{score}, hscore{hscore}, count{count}{}

Record:: ~Record(){}

//void Record:: notify(std::vector<std::vector <Cell>>& grid){}

int Record::getlevel(){
    return level;
}
int Record::getcount(){
    return count;
}
void Record::levelup(){
    if(level<4){
        level++;
    }
}
void Record::leveldown(){
    if(level>0){
        level--;
    }
}
void Record::addcount(){
    count++;
}
void Record::erasecount(){
    count=0;
}

void Record::setscore(int gain){
    score+=gain;
    if(hscore<score){
        hscore=score;
    }
}
int Record::getscore(){
    return score;
}
int Record::gethscore(){
    return hscore;
}

