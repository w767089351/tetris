#ifndef INFO_H
#define INFO_H
class block;
class Info {
  int count; //# of lines to be cleared
  Block* bp; //pointer to a possible block
public:
  int getc() const;
  Block* getp() const;
  void setc(int c);
  void setp(Block* p);
  Info(int count, Block* bp);
  ~Info();
};
#endif
