#include "block.h"
#include "info.h"

int Info:: getc() const{
  return count;
}
Block* Info:: getp() const{
  return bp;
}
void Info:: setc(int c){
  count = c;
}
void Info:: setp(Block* p){
  bp = p;
}
Info:: Info(int count, Block* bp):count{count},bp{bp}{}

Info:: ~Info(){
  delete bp;
}

