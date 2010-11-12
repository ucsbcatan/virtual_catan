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
    void saveGame();
    void placeSettlement(Player currPlayer, int vertNum);
    void placeFirstSettlement(Player currPlayer, int vertNum);
    void placeRoad(Player currPlayer, int edgeNum);
    void trade(Player player1, Player player2);
    void firstYield();
    void yield();
    int currentScore();
    int currentTime(int clockID);
    int getScore();
    string findLongestRoad();
    Player declareWinner(int playerID);

        playerNum currPlayer;
        vector<Player> myplayerList;
        vector<int> devDeck;
        Gameboard board;
        int numPlayers;
        Dev DevDeck;
        Player currentPlayer;

private:
    int clockID;

    map<int, Player> playerTurnList;

        };
#endif
