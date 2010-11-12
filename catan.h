#ifndef CATAN_H
#define CATAN_H

 // CATAN_H

#include "player.h"
#include <iostream>
#include <stdlib.h>
#include <vector>
// #include <map>


class Catan {
public:
    Catan();
    Catan(int numPlayersIn, vector<string> namesIn);
    void InitializeHand();
    int currentScore();
    void pringPlayerName();
    int currentTime(int clockID);
    void saveGame();
    int getScore();
    string findLongestRoad();
    Player declareWinner(int playerID);

protected:
    //int getScore();
    //void setScore(int point, Player myPlayer);

private:
    int clockID;
    int numPlayers;
    vector<Player> playerList;
    map<int, Player> playerTurnList;

        };
#endif
