#include "board.h"
#include "textdisplay.h"
#include "graphicDisplay.h"
#include "record.h"
#include "block.h"
#include "rect.h"
#include "square.h"
#include "bar.h"
#include "unique.h"
#include "nextGenerator.h"
#include "level0.h"
#include "level1.h"
#include "level2.h"
#include "level3.h"
#include "info.h"
Board:: Board():hiscore{0},graphics{true}{}

Board:: ~Board(){
    for(int i =0; i<blist.size(); i++){
        delete blist[i]; 
    }
    delete record;
    delete level_0;
    delete level_1;
    delete level_2;
    delete level3_4;
    delete td;
    if(graphics==true){	
       delete gd;
    }
}

void Board:: init(std::string level0file,bool graphics){
    const int width = 11;
    const int height = 18;
    this->graphics=graphics;
    //hiscore=record->gethscore();
    grid.clear();
    for(int i=0; i<blist.size(); i++){
        delete blist[i];
    }
    blist.clear();
    delete td;
    delete record;
    delete level_0;
    delete level_1;
    delete level_2;
    delete level3_4;
    if(graphics==true){
        delete gd;      //delete
        gd=new GraphicsDisplay(); //new graphic Display
    }
    td = new TextDisplay();
    /////////
    dettach();
    record = new Record(0,0,hiscore,0);
    level_0=new Level0(level0file);
    level_1=new Level1();
    level_2=new Level2();
    level3_4=new Level3();
    /////////
    // if(!record){
    //   record = new Record(0, 0, 0, 0);
    //   attach(record);
    // }
    for(int r=0;r<height;r++){//row
        std::vector <Cell>v;
        for(int c=0;c<width;c++){//col
            Cell cell{r, c, 0, ' '};
            v.push_back(cell);
        }
        grid.push_back(v);
    }
    
    attach(td);
    if(graphics==true){
        attach(gd);
        //attach graphic display
    }
    //
    //std::cout<<"observers.size()"<<observers.size()<<std::endl;
    setBlock('A',true,true,"");
    
    //reserved to attach graphicsdisplay
    notifyObservers(*this);
}

void Board:: move(const int distance, const int isDown){
    auto curr = blist[blist.size() - 1];
    if(isDown){
        for(int z=0; z<distance; z++) curr->goDown(1, grid); //move down
    }else if(distance>0){
        for(int z=0; z<distance; z++) curr->go(1, grid); //move r or l
    }else{
        for(int z=0; z>distance; z--) curr->go(-1, grid);
    }
    notifyObservers(*this);
}

void Board:: rotate(const int isCounter){
    auto curr = blist[blist.size() - 1];
    if(isCounter) curr->crotate_wrap(grid);
    else curr->rotate_wrap(grid);
    notifyObservers(*this);
}
/**
void Board:: reset(const char k, Block* bp){
    int pos = blist.size()-1;
    Block* b = nullptr;
    auto tmp = blist[pos];
    for(auto p : tmp->getList()){
        if(!p)continue;
        p->changeState(10);
    }
    blist.erase(blist.begin() + pos);
    delete tmp;
    
    std::vector<Cell*> lst;
    for(int i=0; i<6; i++){
        if(! bp->getList()[i]){
            lst.emplace_back(nullptr);
            continue;
        }
        int r = bp->getList()[i]->getr();
        int c = bp->getList()[i]->getc();
        lst.emplace_back(&grid[r][c]);
        grid[r][c].changeKind(k);
        grid[r][c].changeState(1);
    }
    if(k == 'I') b = new Bar(lst);
    else if(k == 'O') b = new Square(lst);
    else b = new Rect(lst);
    addBlock(b);
}
**/
void Board:: reset(const char k, Block* bp){
    auto curr = blist[blist.size()-1];
    for(auto p : curr->getList()){
        if(!p)continue;
        p->changeState(10);
    }
    
    for(int i=0; i<6; i++){
        if(! bp->getList()[i]){
            curr->getList()[i]=nullptr;
            continue;
        }
        int r = bp->getList()[i]->getr();
        int c = bp->getList()[i]->getc();
        
        curr->getList()[i] = &grid[r][c];
        grid[r][c].changeKind(k);
        grid[r][c].changeState(1);
    }
}
int Board:: setBlock(const char kind,bool init,bool norand,std::string norandfile){
    //Block* b;
    char k=next;
    next = kind;
    int block_level=record->getlevel();
    int success=1;
    record->addcount();
    if(block_level==0){
        b=level_0->generate_wrap(grid,success,k,next,init,norand,norandfile);
    }
    else if(block_level==1){
        b=level_1->generate_wrap(grid,success,k,next,init,norand,norandfile);
    }
    else if(block_level==2){
        b=level_2->generate_wrap(grid,success,k,next,init,norand,norandfile);
    }
    else if(block_level==3){
        b=level3_4->generate_wrap(grid,success,k,next,init,norand,norandfile);
    }
    else{
        if(grid[3][5].getState()){
            delete b;
	    return 0;
        }
        if((record->getcount()-1)%5==0){
            //initiate the unique block
            std::vector<Cell*> lst;
            lst.emplace_back(&grid[0][0]);
            lst.emplace_back(nullptr);
            lst.emplace_back(nullptr);
            lst.emplace_back(nullptr);
            lst.emplace_back(nullptr);
            lst.emplace_back(nullptr);
            lst[0]->changeKind('*');
            lst[0]->changeState(1);
            b=new Unique(lst);
            addBlock(b);
            auto curr = blist[blist.size() - 1];
            curr->go(5,grid);
            drop();
        }
        b=level3_4->generate_wrap(grid,success,k,next,false,norand,norandfile);
    }
    if(success==0){
	delete b;
        return 0;
    }
    b->setlevel(record->getlevel());
    
    addBlock(b);
    auto curr = blist[blist.size() - 1];
    curr->goDown(3, grid); //move down
    notifyObservers(*this);
    return 1;
}

void Board:: remBlock(){
    int s=blist.size();
    for(int i=0; i<s; i++){
        for(int j=0; j<6; j++){
            if(blist[i]->getList()[j]!=nullptr) break;
            if(j == (blist[i]->getList().size() - 1)){
                auto p = blist[i];
                int calc=p->getlevel();
                record->setscore((calc+1)*(calc+1));
                blist.erase(blist.begin() + i);
                delete p;
                i--;
            }
        }
    }
}

void Board:: addBlock(Block* b){
    blist.emplace_back(b);
}

int Board:: checkFull() const{
    for(int r=grid.size() - 1; r > 0; r--){
        for(int c=0; c< grid[r].size(); c++){
            if(!grid[r][c].getState())break;
            if(c==grid[r].size()-1){
                record->erasecount();
                return r;
            }
        }
    }
    return -1;
}
int Board:: countFull() const{
    int count = 0;
    for(int r=grid.size() - 1; r > 0; r--){
        for(int c=0; c< grid[r].size(); c++){
            if(!grid[r][c].getState())break;
            else if(c==grid[r].size()-1)++count;
        }
    }
    return count;
}

void Board:: setFree(const int freeRow){
    for(int i=0; i<blist.size(); i++){
        for(int j=0; j<blist[i]->getList().size(); j++){
            if(!(blist[i]->getList()[j])) continue;
            int r = blist[i]->getList()[j]->getr();
            if(r==freeRow){
                Cell* cell = blist[i]->getList()[j];
                blist[i]->remCell(cell);
                
            }
        }
    }
}

int Board:: drop(){
    auto curr = blist[blist.size() - 1];
    for(int i=0; i<grid.size(); i++){
        if(! curr->goDown(1, grid))break;
    }//the block goes down as much as possible
    int r = checkFull();
    int count_line=0;
    while(r != -1){//loop as long as there's full row
        
        setFree(r);
        count_line++;
        for(int i = r; i>=0; i--){
            if(i==0)break;
            for(int j=0; j< grid[i].size(); j++){
                if(grid[i-1][j].getState()){
                    grid[i][j].changeState(11);
                    grid[i][j].changeKind(grid[i-1][j].getKind());
                }
                else{
                    grid[i][j].changeState(10);
                }
            }
        }
        //update every relevant block cellptr by point to the one below
        for(int k = 0; k<blist.size(); k++){
            for(int l = 0; l<blist[k]->getList().size(); l++){
                if(! blist[k]->getList()[l]) continue;
                int row = blist[k]->getList()[l]->getr();
                int col = blist[k]->getList()[l]->getc();
                if(row <r) blist[k]->getList()[l] = &(grid[row+1][col]);
            }
        }
        r = checkFull();
    }
    if(count_line!=0){
        record->setscore((count_line+record->getlevel())*(count_line+record->getlevel()));
    }
    remBlock();
    notifyObservers(*this);
    //std::cout<<"Score:"<<record->getscore()<<std::endl;
    //std::cout<<"High: Score:"<<record->gethscore()<<std::endl;
    hiscore=record->gethscore();
    for(int i=0; i<curr->getList().size(); i++){
        if(!curr->getList()[i]) continue;
        if(curr->getList()[i]->getr()<3) return 0;
    }
    return 1;
}
/**
void Board:: hint(){
    std::cout<<blist.size() - 1<<std::endl;
    auto curr = blist[blist.size() - 1];
    auto cpy = curr->copy_wrap();
    std:: vector<Info*> v;
    char k;
    int cleared;
    int state;
    int isCW = 1;
    //step1: set up the loop that moved r each time
    for(auto e:curr->getList()){
        if(!e)continue;
        else{ k = e->getKind(); break;}
    }//gets k
    
    //std::cout<<"1"<<std::endl;
    for(int i=0; i<11; i++){
        auto curr = blist[blist.size() - 1];
        for(int q=0; q<11; q++)curr->go(-1, grid);
        //move to the very left
        int s = curr->go(i, grid);
        //std::cout<<"2"<<std::endl;
        if(!s)break;
        //std::cout<<"3"<<std::endl;
        for(int j=0; j<4; j++){
            //std::cout<<"4"<<std::endl;
            for(int q=1; q<15; q++){
                curr->goDown(1, grid);
            }
            //std::cout<<"5"<<std::endl;
            cleared = countFull();
            //std::cout<<"a"<<std::endl;
            Info* in = new Info(cleared, curr->copy_wrap());
            //std::cout<<"b"<<std::endl;
            v.emplace_back(in);
            //std::cout<<"6"<<std::endl;
            if(isCW) state=curr->rotate_wrap(grid);
            else state=curr->crotate_wrap(grid);
            if((isCW)&&(!state)){
                for(int k=j; k>0; k--) curr->crotate_wrap(grid);
                //clockwise failed so go back to original state and try counter
                j=0; isCW=0;
            }
            if((!isCW)&&(!state)) break;
            //std::cout<<"66"<<std::endl;
        }
        isCW = 1;
        //std::cout<<"7"<<std::endl;
        reset(k, cpy);
        //std::cout<<"8"<<std::endl;
    }
    
    //Step2: analyze the best pos
    int max = 0;
    Block* ma = nullptr;
    //check1:get the pos that clears the most lines
    for(auto e: v) if(e->getc()>max){ ma=e->getp(); max=e->getc();}
    if(max>0){
        td->hint(ma);
        for(int r=0; r<v.size();r++) delete v[r];
        delete cpy;
        return;}//best fit
    
    int highest = 0;
    //check2:get the "highest" pos
    for(auto e: v){
        auto c = e->getp()->geth(0);
        int r = c->getr();
        if(r>highest){ma=e->getp(); highest=r;}

    }
   if(graphics==true){
    gd->hint(ma);
   } 
   td->hint(ma);
for(int r=0; r<v.size();r++) delete v[r];
reset(k, cpy);   
 delete cpy;
}
**/
/**
void Board:: hint(){
    std::cout<<blist.size() - 1<<std::endl;
    auto curr = blist[blist.size() - 1];
    auto cpy = curr->copy_wrap();
    std:: vector<Info*> v;
    char k;
    int cleared;
    int state;
    int isCW = 1;
    //step1: set up the loop that moved r each time
    for(auto e:curr->getList()){
        if(!e)continue;
        else{ k = e->getKind(); break;}
    }//gets k
    int num =0;//num of successful rotate
    for(int j=0; j<8; j++){
      auto curr = blist[blist.size() - 1];
      if(j<4)curr->rotate_wrap(grid);
      else curr->crotate_wrap(grid);
    for(int i=0; i<11; i++){
        for(int q=0; q<11; q++)curr->go(-1, grid); //move to the very left
        int s = curr->go(i, grid);
        if(!s)break;
        for(int j=0; j<4; j++){
            for(int q=1; q<15; q++){
                curr->goDown(1, grid);
            }
            cleared = countFull();
            Info* in = new Info(cleared, curr->copy_wrap());
            v.emplace_back(in);
            if(isCW) state=curr->rotate_wrap(grid);
            else state=curr->crotate_wrap(grid);
            if((isCW)&&(!state)){
                for(int k=j; k>0; k--) curr->crotate_wrap(grid);
                //clockwise failed so go back to original state and try counter
                j=0; isCW=0;
            }
            if((!isCW)&&(!state)) break;
        }
        isCW = 1;
        reset(k, cpy);
    }
  }
    //Step2: analyze the best pos
    int max = 0;
    Block* ma = nullptr;
    //check1:get the pos that clears the most lines
    for(auto e: v) if(e->getc()>max){ ma=e->getp(); max=e->getc();}
    if(max>0){
      if(graphics==true){
        gd->hint(ma);
      }
      td->hint(ma);
      for(int r=0; r<v.size();r++) delete v[r];
      delete cpy;
      return;
    }//best fit
    int highest = 0;
    int spacec = 0;
    for(auto e: v){
        int space = 0;//num of space below
        int r = e->getp()->geth(0)->getr();
        if(r>highest){ma=e->getp(); highest=r; continue;}
        //check3:get the pos with minimum space below
        if(r==highest){//calculate the num of spaces below the available position.
        int ur = e->getp()->geth(0)->getr();//upper row
        int lr = e->getp()->geth(1)->getr();//lower row
        int uc = e->getp()->getv(1)->getc();//upper col
        int lc = e->getp()->getv(0)->getc();//lower col

        int lowerp = lr+1;
        if(lr!=17){
          for(int i=lc; i<=uc; i++){
            if(!grid[lowerp][i].getState())++space;
          }
        }
        if(ur>highest){   //check2:get the pos with "highest" row
          ma=e->getp();
          highest=ur;
          spacec = space;
        }
        else if(ur==highest){
          if(space<spacec){
            ma=e->getp();
            highest=ur;
            spacec = space;
          }
        }
      }
    }
    if(graphics==true){
      gd->hint(ma);
    }
    td->hint(ma);

    for(int r=0; r<v.size();r++) delete v[r];
    reset(k, cpy);
    delete cpy;
}
**/
//new hint
/**
void Board:: hint(){
    std::cout<<blist.size() - 1<<std::endl;
    auto curr = blist[blist.size() - 1];
    auto cpy = curr->copy_wrap();
    std:: vector<Info*> v;
    char k;
    int cleared;
    int state;
    int isCW = 1;
    //step1: set up the loop that moved r each time
    for(auto e:curr->getList()){
        if(!e)continue;
        else{ k = e->getKind(); break;}
    }//gets k
    int num =0;//num of successful rotate
    for(int j=0; j<8; j++){ //loop 1(rotate loop)
      auto curr = blist[blist.size() - 1];
      if(j<4)curr->rotate_wrap(grid);
      else curr->crotate_wrap(grid);
    for(int i=0; i<11; i++){ //loop 2(right loop)
        for(int q=0; q<11; q++)curr->go(-1, grid); //move to the very left
        int s = curr->go(i, grid);
        if(!s)break;
        for(int j=0; j<4; j++){ //loop 3(rotate loop)
          for(int y=0; y<22; y++){ //loop 2(right loop)
            if(y<11)for(int m=0; m<y; m++)curr->go(1, grid);
            else for(int m=0; m<y; m++)curr->go(-1, grid);
            for(int q=1; q<15; q++) curr->goDown(1, grid); //go all the way down
            cleared = countFull();
            Info* in = new Info(cleared, curr->copy_wrap());
            v.emplace_back(in);
            if(isCW) state=curr->rotate_wrap(grid);
            else state=curr->crotate_wrap(grid);
            if((isCW)&&(!state)){
                for(int k=j; k>0; k--) curr->crotate_wrap(grid);
                //clockwise failed so go back to original state and try counter
                j=0; isCW=0;
            }
            if((!isCW)&&(!state)) break;
          }
        }
        isCW = 1;
        reset(k, cpy);
    }
  }
    //reset(k, cpy);
    //Step2: analyze the best pos
    int max = 0;
    Block* ma = nullptr;
    //check1:get the pos that clears the most lines
    for(auto e: v) if(e->getc()>max){ ma=e->getp(); max=e->getc();}
    if(max>0){
      if(graphics==true){
        gd->hint(ma);
      }
      td->hint(ma);
      for(int r=0; r<v.size();r++) delete v[r];
      delete cpy;
      return;
    }//best fit
    int highest = 0;
    int spacec = 0;
    for(auto e: v){
        int space = 0;//num of space below
        int r = e->getp()->geth(0)->getr();
        if(r>highest){ma=e->getp(); highest=r; continue;}
        //check3:get the pos with minimum space below
        if(r==highest){//calculate the num of spaces below the available position.
        int ur = e->getp()->geth(0)->getr();//upper row
        int lr = e->getp()->geth(1)->getr();//lower row
        int uc = e->getp()->getv(1)->getc();//upper col
        int lc = e->getp()->getv(0)->getc();//lower col

        int lowerp = lr+1;
        if(lr!=17){
          for(int i=lc; i<=uc; i++){
            if(!grid[lowerp][i].getState())++space;
          }
        }
        if(ur>highest){   //check2:get the pos with "highest" row
          ma=e->getp();
          highest=ur;
          spacec = space;
        }
        else if(ur==highest){
          if(space<spacec){
            ma=e->getp();
            highest=ur;
            spacec = space;
          }
        }
      }
    }
    if(graphics==true){
      gd->hint(ma);
    }
    td->hint(ma);
    for(int r=0; r<v.size();r++) delete v[r];
    reset(k, cpy);
    delete cpy;
}
**/
/**
void Board:: hint(){
    std::cout<<blist.size() - 1<<std::endl;
    auto curr = blist[blist.size() - 1];
    auto cpy = curr->copy_wrap();
    std:: vector<Info*> v;
    char k;
    int cleared;
    int state;
    int isCW = 1;
    //step1: set up the loop that moved r each time
    for(auto e:curr->getList()){
        if(!e)continue;
        else{ k = e->getKind(); break;}
    }//gets k
    int num =0;//num of successful rotate
    for(int j=0; j<8; j++){
      auto curr = blist[blist.size() - 1];
      if(j<4)curr->rotate_wrap(grid);
      else curr->crotate_wrap(grid);
    for(int i=0; i<11; i++){
        for(int q=0; q<11; q++)curr->go(-1, grid); //move to the very left
        int s = curr->go(i, grid);
        if(!s)break;
        for(int j=0; j<4; j++){
          for(int y=0; y<11; y++){
            for(int q=1; q<15; q++)curr->goDown(1, grid);
            cleared = countFull();
            Info* in = new Info(cleared, curr->copy_wrap());
            v.emplace_back(in);
            if(isCW) state=curr->rotate_wrap(grid);
            else state=curr->crotate_wrap(grid);
            if((isCW)&&(!state)){
                for(int k=j; k>0; k--) curr->crotate_wrap(grid);
                //clockwise failed so go back to original state and try counter
                j=0; isCW=0;
            }
            if((!isCW)&&(!state)) break;
          }
        }
        isCW = 1;
        reset(k, cpy);
    }
  }
  //Step2: analyze the best pos
    int max = 0;
    Block* ma = nullptr;
    //check1:get the pos that clears the most lines
    for(auto e: v) if(e->getc()>max){ ma=e->getp(); max=e->getc();}
    if(max>0){
      if(graphics==true){
        gd->hint(ma);
      }
      td->hint(ma);
      for(int r=0; r<v.size();r++) delete v[r];
      delete cpy;
      return;
    }//best fit
    int highest = 0;
    int spacec = 0;
    for(auto e: v){
        int space = 0;//num of space below
        int r = e->getp()->geth(0)->getr();
        if(r>highest){ma=e->getp(); highest=r; continue;}
        //check3:get the pos with minimum space below
        if(r==highest){//calculate the num of spaces below the available position.
        int ur = e->getp()->geth(0)->getr();//upper row
        int lr = e->getp()->geth(1)->getr();//lower row
        int uc = e->getp()->getv(1)->getc();//upper col
        int lc = e->getp()->getv(0)->getc();//lower col

        int lowerp = lr+1;
        if(lr!=17){
          for(int i=lc; i<=uc; i++){
            if(!grid[lowerp][i].getState())++space;
          }
        }
        if(ur>highest){   //check2:get the pos with "highest" row
          ma=e->getp();
          highest=ur;
          spacec = space;
        }
        else if(ur==highest){
          if(space<spacec){
            ma=e->getp();
            highest=ur;
            spacec = space;
          }
        }
      }
    }
    if(graphics==true){
      gd->hint(ma);
    }
    td->hint(ma);

    for(int r=0; r<v.size();r++) delete v[r];
    reset(k, cpy);
    delete cpy;
}
**/

void Board:: hint(){
    std::cout<<blist.size() - 1<<std::endl;
    auto curr = blist[blist.size() - 1];
    auto cpy = curr->copy_wrap();
    std:: vector<Info*> v;
    char k;
    int cleared;
    int state;
    int isCW = 1;
    //step1: set up the loop that moved r each time
    for(auto e:curr->getList()){
        if(!e)continue;
        else{ k = e->getKind(); break;}
    }//gets k
    int num =0;//num of successful rotate
  for(int y=0; y<22; y++){
    for(int j=0; j<8; j++){
      auto curr = blist[blist.size() - 1];
      if(j<4)curr->rotate_wrap(grid);
      else curr->crotate_wrap(grid);
    for(int i=0; i<11; i++){
        for(int q=0; q<11; q++)curr->go(-1, grid); //move to the very left
        int s = curr->go(i, grid);
        if(!s)break;  
          if(y<11){for(int m=0; m<y; m++)curr->go(1, grid);}
          else{ for(int m=0; m<y; m++)curr->go(-1, grid);}
          for(int j=0; j<4; j++){
            for(int q=1; q<15; q++)curr->goDown(1, grid);
            cleared = countFull();
            Info* in = new Info(cleared, curr->copy_wrap());
            v.emplace_back(in);
            if(isCW) state=curr->rotate_wrap(grid);
            else state=curr->crotate_wrap(grid);
            if((isCW)&&(!state)){
                for(int k=j; k>0; k--) curr->crotate_wrap(grid);
                //clockwise failed so go back to original state and try counter
                j=0; isCW=0;
            }
            if((!isCW)&&(!state)) break;
          }
        isCW = 1;
        reset(k, cpy);
      }
    }
  }
  //Step2: analyze the best pos
    int max = 0;
    Block* ma = nullptr;
    //check1:get the pos that clears the most lines
    for(auto e: v) if(e->getc()>max){ ma=e->getp(); max=e->getc();}
    if(max>0){
      if(graphics==true){
        gd->hint(ma);
      }
      td->hint(ma);
      for(int r=0; r<v.size();r++) delete v[r];
      delete cpy;
      return;
    }//best fit
    int highest = 0;
    int spacec = 0;
    for(auto e: v){
        int space = 0;//num of space below
        int r = e->getp()->geth(0)->getr();
        if(r>highest){ma=e->getp(); highest=r; continue;}
        //check3:get the pos with minimum space below
        if(r==highest){//calculate the num of spaces below the available position.
        int ur = e->getp()->geth(0)->getr();//upper row
        int lr = e->getp()->geth(1)->getr();//lower row
        int uc = e->getp()->getv(1)->getc();//upper col
        int lc = e->getp()->getv(0)->getc();//lower col

        int lowerp = lr+1;
        if(lr!=17){
          for(int i=lc; i<=uc; i++){
            if(!grid[lowerp][i].getState())++space;
          }
        }
        if(ur>highest){   //check2:get the pos with "highest" row
          ma=e->getp();
          highest=ur;
          spacec = space;
        }
        else if(ur==highest){
          if(space<spacec){
            ma=e->getp();
            highest=ur;
            spacec = space;
          }
        }
      }
    }
    if(graphics==true){
      gd->hint(ma);
    }
    td->hint(ma);

    for(int r=0; r<v.size();r++) delete v[r];
    reset(k, cpy);
    delete cpy;
}
int Board:: resetBlock(const char k,bool norand,std::string norandfile){
    int pos = blist.size()-1;
    auto tmp = blist[pos];
    for(auto p : tmp->getList()){
        if(!p)continue;
        p->changeState(10);
    }
    blist.erase(blist.begin() + pos);
    delete tmp;
    return setBlock(k,false,norand,norandfile);
}

void Board::levelUp(){
    record->levelup();
    notifyObservers(*this);
}
void Board::levelDown(){
    record->leveldown();
    notifyObservers(*this);
}
int Board::getlevel(){
    return record->getlevel();
}
char Board::getnext(){
    return next;
}
int Board::getscore(){
    return record->getscore();
}
int Board::gethscore(){
    return record->gethscore();
}

std::ostream &operator<<(std::ostream &out, const Board &board){
    out<<"Level:     "<<board.record->getlevel()<<std::endl;
    out<<"Score:     "<<board.record->getscore()<<std::endl;
    out<<"Hi Score:  "<<board.hiscore<<std::endl;
    out<<"-----------"<<std::endl;
    out << *(board.td);
    out<<"-----------"<<std::endl;
    out<<"Next:"<<std::endl;
    if(board.next == 'I'){
        out<<"IIII"<<std::endl;
    }else if(board.next=='O'){
        out<<"OO"<<std::endl;
        out<<"OO"<<std::endl;
    }else if(board.next == 'J'){
        out<<"J  "<<std::endl;
        out<<"JJJ"<<std::endl;
    }else if(board.next == 'L'){
        out<<"  L"<<std::endl;
        out<<"LLL"<<std::endl;
    }else if(board.next == 'S'){
        out<<" SS"<<std::endl;
        out<<"SS "<<std::endl;
    }else if(board.next == 'Z'){
        out<<"ZZ"<<std::endl;
        out<<" ZZ"<<std::endl;
    }else{
        out<<"TTT"<<std::endl;
        out<<" T "<<std::endl;
    }
    return out;
}
std::vector<std::vector <Cell>>& Board::getGrid(){
    return grid;
}

