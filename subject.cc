#include "subject.h"
#include "board.h"
#include <iostream>///to be removed
void Subject:: attach(Observer* obs){
    observers.emplace_back(obs);
}
void Subject:: notifyObservers(Board& s){
    for (auto& ob : observers) ob->notify(s);
}
void Subject:: dettach(){
    for (int i = 0; i<observers.size(); i++){
        observers.erase(observers.begin()+i);
    }
}


