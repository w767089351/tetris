//
//  main.cpp
//  quadris
//
//  Created by Jiayu Shao on 2017-11-26.
//  Copyright © 2017 Jiayu Shao. All rights reserved.
//


//d.r.o.p

#include <string>
#include <stdlib.h>
#include <iostream>
#include "command.h"
#include "board.h"
#include <fstream>
#include <time.h>
using namespace std;


int main(int argc, char *argv[]) {
    
    string level0file="sequence.txt";
    //srand(seed)++ %6;
    int setlevel=0;
    bool graphics=true;
    int seed=1;
    for(int i=1;i<argc;i++){
        string cmdline=argv[i];
        if(cmdline=="-text"){
            graphics=false;
        }
        else if(cmdline=="-seed"){
            seed=atoi(argv[i+1]);
            i++;
            srand(seed);
        }
        else if(cmdline=="-scriptfile"){
            level0file = argv[i+1];
            i++;
        }
        else{
            setlevel=atoi(argv[i+1]);
            i++;
            
        }
    }
    
    //srand(time(NULL));
    //cin
    string cmd;
    //create a board
    Board b;
    Command c;
    int count=0;
    b.init(level0file,graphics);
    int endgame=1;
    cout<<b<<endl;
    bool testing= false;
    bool norand=false;
    ifstream myfile;
    string norandfilename;
    
    
    while(true){
        //read command
        if(testing==false){
            cin>>cmd;
            if(cin.eof()){
                break;
            }
        }
        else{
            //Get the command in the file
            myfile>>cmd;
            if(myfile.eof()){
                myfile.close();
                testing=false;
            }
        }
        //interpret command
        c.interpreter(cmd, count);
        //loop command
        if(cmd=="norandom"){
            //cout<<"norandom function has been called"<<endl;
            cin>>norandfilename;
            if(b.getlevel()>=3){
                norand=true;
            }
        }
        else if(cmd=="random"){
            //cout<<"random function has been called"<<endl;
            //restores level
            if(b.getlevel()>=3){
                norand=false;
            }
        }
        else if(cmd=="rename"){
            //finished
            //cout<<"rename function has been called"<<endl;
            string old;
            string n;
            cin>>old;
            cin>>n;
            c.interpreter(old, count);
            c.changeName(old,n);
        }
        else if(cmd=="sequence"){
            //cout<<"sequence function has been called"<<endl;
            string file_name;
            //Get the file name
            cin>>file_name;
            myfile.open(file_name);
            testing=true;
            
        }
        else if(cmd=="I"){
            //cout<<"I function has been called"<<endl;
            b.resetBlock('I',norand,norandfilename);
            //b.setBlock('I');
        }
        else if(cmd=="J"){
            //cout<<"J function has been called"<<endl;
            b.resetBlock('J',norand,norandfilename);
            //b.setBlock('J');
        }
        else if(cmd=="L"){
            //cout<<"L function has been called"<<endl;
            b.resetBlock('L',norand,norandfilename);
            //b.setBlock('L');
        }
        else if(cmd=="O"){
            //cout<<"O function has been called"<<endl;
            b.resetBlock('O',norand,norandfilename);
            //b.setBlock('O');
        }
        else if(cmd=="S"){
            //cout<<"S function has been called"<<endl;
            b.resetBlock('S',norand,norandfilename);
            //b.setBlock('S');
        }
        else if(cmd=="Z"){
            //cout<<"Z function has been called"<<endl;
            b.resetBlock('Z',norand,norandfilename);
            //b.setBlock('Z');
        }
        else if(cmd=="T"){
            //cout<<"T function has been called"<<endl;
            b.resetBlock('T',norand,norandfilename);
            //b.setBlock('T');
        }
        else if(cmd=="hint"){
            //cout<<"hint function has been called"<<endl;
            //b.resetBlock();
            b.hint();
        }
        else if(cmd=="restart"){
            //cout<<"restart function has been called"<<endl;
            b.init(level0file,graphics);
        }
        else if(cmd=="nomatch"){
            //cout<<"nomatch function has been called"<<endl;
            cout<<"no matching commands"<<endl;
        }
        else if(cmd=="mulmatch"){
           // cout<<"multiple function has been called"<<endl;
            cout<<"multiple commands matching"<<endl;
        }
        else if(cmd=="left"){
            //finished
            //cout<<"left function has been called"<<count<<endl;
            b.move(-1*count,0);
        }
        else if(cmd=="right"){
            //finished
            //cout<<"right function has been called"<<endl;
            b.move(count,0);
        }
        else if(cmd=="down"){
            //finished
            //cout<<"down function has been called"<<endl;
            b.move(count,1);
        }
        else{
            for(int i=0;i<count;i++){
                if(cmd=="clockwise"){
                    //cout<<"clockwise function has been called"<<endl;
                    b.rotate(0);
                }
                else if(cmd=="counterclockwise"){
                    //cout<<"counterclockwise function has been called"<<endl;
                    b.rotate(1);
                }
                else if(cmd=="drop"){
                    //cout<<"drop function has been called"<<endl;
                    //setblock
                    endgame=b.drop();
                    if(endgame==0){
                        cout<<"You lost. See you next time~"<<endl;
                        return 0;
                    }
                    else{
                        endgame=b.setBlock('A',false,norand,norandfilename);
                        if(endgame==0){
                            cout<<b<<endl;
                            cout<<"Cannot Place Anymore. You lost. See you next time~"<<endl;
                            return 0;
                        }
                    }
                }
                else if(cmd=="levelup"){
                    //cout<<"levelup function has been called"<<endl;
                    //level up
                    b.levelUp();
                }
                else if(cmd=="leveldown"){
                    //cout<<"leveldown function has been called"<<endl;
                    //level down
                    b.levelDown();
                }
            }
        }
        if(b.getlevel()>=3 && (cmd=="left"||cmd=="right"||cmd=="down"||cmd=="clockwise"||cmd=="counterclockwise"||cmd=="drop")){
            b.move(1, 1);
        }
        //set level from command line
        for(int i=0;i<setlevel;i++){
            b.levelUp();
        }
        cout<<b<<endl;
    }
    
    return 0;
}

