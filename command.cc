#include "command.h"

Command::Command():size{0}{
    slist.push_back("left");
    slist.push_back("right");
    slist.push_back("down");
    slist.push_back("clockwise");
    slist.push_back("counterclockwise");
    slist.push_back("drop");
    slist.push_back("levelup");
    slist.push_back("leveldown");
    slist.push_back("norandom");
    slist.push_back("random");
    slist.push_back("sequence");
    slist.push_back("I");
    slist.push_back("J");
    slist.push_back("L");
    slist.push_back("O");
    slist.push_back("S");
    slist.push_back("Z");
    slist.push_back("T");
    slist.push_back("hint");
    slist.push_back("restart");
    slist.push_back("rename");
    
    orglist.push_back("left");
    orglist.push_back("right");
    orglist.push_back("down");
    orglist.push_back("clockwise");
    orglist.push_back("counterclockwise");
    orglist.push_back("drop");
    orglist.push_back("levelup");
    orglist.push_back("leveldown");
    orglist.push_back("norandom");
    orglist.push_back("random");
    orglist.push_back("sequence");
    orglist.push_back("I");
    orglist.push_back("J");
    orglist.push_back("L");
    orglist.push_back("O");
    orglist.push_back("S");
    orglist.push_back("Z");
    orglist.push_back("T");
    orglist.push_back("hint");
    orglist.push_back("restart");
    orglist.push_back("rename");
}


void Command::interpreter(std::string& command,int& count){
    int count_invalid=0;
    count=1;
    //seperate the string
    int count_dig=0;
    std::string tmp;
    
    while(count_dig<command.size() && isdigit(command.at(count_dig))){
        count_dig++;
    }
    //std::cout<<"count digit"<<count_dig<<std::endl;
    
    //cast string into int
    if(count_dig>0){
        count=std::stoi(command.substr(0,count_dig));
        if(count_dig!=command.size()){
	//reset command
        command=command.substr(count_dig);
    	}
	else{
	command=command+"nomatch";
	command=command.substr(count_dig);
	}
      }
    
    size=command.size();
    
    //use a loop to do so
    for(int i=0;i<slist.size();i++){
        if(command==slist[i].substr(0,size)){
            tmp=orglist[i];
            count_invalid++;
            //std::cout<<count_invalid<<std::endl;
        }
    }
    
    //invalid input: no such commands
    if(count_invalid==0){
        command="nomatch";
        count=0;
    }
    //invalid input: multiple commands being called
    else if(count_invalid>1){
        command="mulmatch";
        count=0;
    }
    else{
        command=tmp;
    }
    
}

void Command::changeName(std::string old_n,std::string new_n){
    for(auto &n:slist){
        if(n==old_n){
            n=new_n;
        }
    }
}


