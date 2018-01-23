#include "textdisplay.h"
#include "subject.h"
#include "cell.h"
#include "block.h"
#include "board.h"
TextDisplay:: TextDisplay(){
    std::vector<char> v1(width, ' ');
    std::vector<std::vector<char>> v2(height, v1);
    td = v2;
}

void TextDisplay:: notify(Board& b){
    auto grid = b.getGrid();
    for(int i =0; i<grid.size(); i++){
        for(int j =0; j<grid[i].size(); j++){
            if(grid[i][j].getState())td[i][j]=grid[i][j].getKind();
            else td[i][j] = ' ';
        }
    }
}

void TextDisplay:: hint(Block* b){
    for(auto e:b->getList()){
        if(!e)continue;
        int r = e->getr();
        int c = e->getc();
        td[r][c] = '?';
    }
}
std::ostream& operator<<(std::ostream &out, const TextDisplay &t){
    for(int i=0; i<t.height; i++){
        for(int j=0; j<t.width; j++){
            out<<t.td[i][j];
        }
        out<<std::endl;
    }
    return out;
}

TextDisplay:: ~TextDisplay(){}
