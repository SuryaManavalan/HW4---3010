#ifndef PLAYER_H
#define PLAYER_H

#include "pawn.h"

class Player
{
public:
    Player(int pnum, Pawn* pawn);
    Pawn* getPawn() {return pawn_;};
    int getCurrSqr() {return currSqr;};
    void setCurrSqr(int n) {currSqr = n;};
    int getPrevSqr() {return prevSqr;};
    void setPrevSqr(int n) {prevSqr = n;};
    int getUndos() {return undos;};
    void useUndos() {undos++;};
    int getRerolls() {return rerolls;};
    void useReroll() {rerolls++;}
private:
    Pawn *pawn_;
    int pnum_;
    int currSqr = 0;
    int prevSqr = 0;
    int undos = 0;
    int rerolls = 0;
};

#endif // PLAYER_H
