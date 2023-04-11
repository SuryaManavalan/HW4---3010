#include "manager.h"

Manager::Manager()
{
    players_ = {};

}

void Manager::addPlayer(Player* p){
    players_.push_back(p);
}

void Manager::nextTurn(){
    if(turn_ == players_.size()){
        turn_ = 1;
    }else{
        turn_++;
    }
}

void Manager::setRoll(int n){
    roll_ = n;
}
