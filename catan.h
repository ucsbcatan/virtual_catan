#ifndef CATAN_H
#define CATAN_H

 // CATAN_H

#include "player.h"
#include "gameboard.h"
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
    int currentTime(int clockID);
    void saveGame();
    int getScore();
    string findLongestRoad();
    Player declareWinner(int playerID);


        vector<Player> myplayerList;
        unsigned int numPlayers;
        Gameboard board;

private:
    int clockID;

    map<int, Player> playerTurnList;

        };
#endif
