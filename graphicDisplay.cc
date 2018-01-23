#include "graphicDisplay.h"
#include "subject.h"
#include "string"
#include "board.h"
#include "cell.h"
#include "block.h"
using namespace std;

GraphicsDisplay::GraphicsDisplay():w{350,500}{
w.fillRectangle(0, 0, 350, 100, Xwindow::Blue);
w.fillRectangle(52, 100, 245, 400, Xwindow::White);
w.fillRectangle(0, 100, 52, 400, Xwindow::Blue);
w.fillRectangle(298, 100, 52, 400, Xwindow::Blue);
w.drawBigString(120, 80, "QUADRIS", Xwindow::Black);
}

void GraphicsDisplay::hint(Block* b){
  for(int i=0; i<6; i++){
   if(! b->getList()[i])continue;
   int r=b->getList()[i]->getr();
   int c=b->getList()[i]->getc();
   w.fillRectangle(52+ c * 22 ,100+ r * 22, 22, 22, Xwindow::Black);
  }
}
void GraphicsDisplay::notify(Board &b) {
    auto grid = b.getGrid();
  int cellSize=22;

for(int i =0; i<grid.size(); i++){
    for(int j =0; j<grid[i].size(); j++){
      if(grid[i][j].getState()){
	char bchar=grid[i][j].getKind();
	if(bchar=='T'){
	w.fillRectangle(52+ grid[i][j].getc() * cellSize ,100+ grid[i][j].getr() * cellSize, cellSize, cellSize, Xwindow::Red);
	}
	else if(bchar=='S'){
	w.fillRectangle(52+ grid[i][j].getc() * cellSize , 100+grid[i][j].getr() * cellSize, cellSize, cellSize, Xwindow::Yellow);
	}
	else if(bchar=='Z'){
	w.fillRectangle(52+ grid[i][j].getc() * cellSize , 100+grid[i][j].getr() * cellSize, cellSize, cellSize, Xwindow::Magenta);
	}
	else if(bchar=='J'){
	w.fillRectangle(52+ grid[i][j].getc() * cellSize , 100+grid[i][j].getr() * cellSize, cellSize, cellSize, Xwindow::Brown);
	}
	else if(bchar=='L'){
	  w.fillRectangle(52+ grid[i][j].getc() * cellSize , 100+grid[i][j].getr() * cellSize, cellSize, cellSize, Xwindow::Cyan);
        }
	else if(bchar=='I'){
	 w.fillRectangle(52+ grid[i][j].getc() * cellSize , 100+grid[i][j].getr() * cellSize, cellSize, cellSize, Xwindow::Green);
    	}
	else if(bchar=='O'){
	 w.fillRectangle(52+ grid[i][j].getc() * cellSize , 100+grid[i][j].getr() * cellSize, cellSize, cellSize, Xwindow::Blue);
	}
	}
	else{
	  w.fillRectangle(52+ grid[i][j].getc() * cellSize , 100+grid[i][j].getr() * cellSize, cellSize, cellSize, Xwindow::White);
	}
     }
  }
string level=to_string(b.getlevel());
string score=to_string(b.getscore());
string hiscore=to_string(b.gethscore());
char next=b.getnext();

w.fillRectangle(0, 100, 52, 400, Xwindow::Blue);
w.fillRectangle(298, 100, 52, 400, Xwindow::Blue);

  w.drawString(300,180, "Next:");
  //w.drawString(320,200, next);
  w.drawString(300,130,"Level:");
  w.drawString(320,150,level);
  w.drawString(5,130,"Score:");
  w.drawString(20,150,score);
  w.drawString(5,180,"HiScore:");
  w.drawString(20,200,hiscore);
cellSize=8;
	if(next=='T'){
       	 w.fillRectangle(305 ,200, 3*cellSize, cellSize, Xwindow::Black);
	w.fillRectangle(305+cellSize ,200+cellSize, cellSize, cellSize, Xwindow::Black);
        }
        else if(next=='S'){
        w.fillRectangle(305+cellSize ,200, 2*cellSize, cellSize, Xwindow::Black);
        w.fillRectangle(305 ,200+cellSize, 2*cellSize, cellSize, Xwindow::Black);}
	else if(next=='O'){

 	w.fillRectangle(305 ,200, 2*cellSize, cellSize, Xwindow::Black);
        w.fillRectangle(305,200+cellSize, 2*cellSize, cellSize, Xwindow::Black);
}
	else if(next=='J'){

	w.fillRectangle(305 ,200, cellSize, cellSize, Xwindow::Black);
        w.fillRectangle(305 ,200+cellSize, 3*cellSize, cellSize, Xwindow::Black);
	}
	else if(next=='Z'){
w.fillRectangle(305 ,200, 2*cellSize, cellSize, Xwindow::Black);
        w.fillRectangle(305+cellSize ,200+cellSize, 2*cellSize, cellSize, Xwindow::Black);
}
	else if(next=='I'){
w.fillRectangle(305 ,200, 4*cellSize, cellSize, Xwindow::Black);

}
	else if(next=='L'){
w.fillRectangle(305+cellSize+cellSize ,200, cellSize, cellSize, Xwindow::Black);
        w.fillRectangle(305 ,200+cellSize,3* cellSize, cellSize, Xwindow::Black);
}
}

