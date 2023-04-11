#ifndef MANAGER_H
#define MANAGER_H

#include "player.h"

class Manager
{
public:
    Manager();
    std::vector<Player*> getPlayers() {return players_;};
    void addPlayer(Player* p);
    int getTurn() {return turn_;};
    void nextTurn();
    int getRoll() { return roll_; };
    void setRoll(int n);
private:
    std::vector<Player*> players_;
    int turn_ = 1;
    int roll_ = 0;
    bool playing_ = true;
};

#endif // MANAGER_H
