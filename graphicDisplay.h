#ifndef GRAPHICSDISPLAY_H
#define GRAPHICSDISPLAY_H
#include "observer.h"
#include "window.h"
#include "board.h"
class Cell;
class Block;
class Board;
class GraphicsDisplay: public Observer {
  Xwindow w;
  bool init;
public:
  GraphicsDisplay();
  void hint(Block* b_hint);
  void notify(Board &b) override;
};
#endif

