#ifndef _TEXTDISPLAY_H_
#define _TEXTDISPLAY_H_
#include <vector>
#include <iostream>
#include "observer.h"
class Block;
class Board;
class TextDisplay: public Observer{
    std:: vector<std::vector <char>> td;
    //note this is a vector of rows
    const int width = 11;
    const int height = 18;
public:
    TextDisplay();
    ~TextDisplay();
    TextDisplay(const TextDisplay& td) = default;
    void hint(Block* b);
    void notify(Board& b)override;
    friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};
#endif
