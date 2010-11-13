#ifndef CATAN_H
#define CATAN_H

 // CATAN_H

#include "player.h"
#include "gameboard.h"
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <map>
#include <sys/time.h>

//This class hold all of the information about the current game being played such as the list of players, the
//gameboard, and the current score.

class Catan {
public:
                     ////////MEMBER FUNCTIONS//////////

    Catan(int numPlayersIn, vector<string> namesIn);     //initialize for NewGame();
    void saveGame();                                     //unimplemented Save Game feature
    void placeSettlement(Player currPlayer, int vertNum);//regular placement of settlement on the gameboard
    void placeFirstSettlement(Player currPlayer, int vertNum);//placement of settlement during the first turn
    void placeRoad(Player currPlayer, int edgeNum);      //player's placement of road on the gameboard
    void trade(Player player1, Player player2);          //function called during the Turn() function in main
    void firstYield();      //happens only during the first turn of the game, giving recourses to all players
    void yield();           //happens at beginnin of every turn, gives players recoursess and checks for winner
    int currentScore();
    int currentTime(int clockID);
    int diceRoll();                                      //Dice Roll for regular turns, returns value 2-12
    int getScore();
    string findLongestRoad();                            //unimplemented determination of which player has "Longest Road"
    Player declareWinner(int playerID);

                       ////////DATA MEMBERS//////////

        playerNum currPlayer;         //keeps track of the current player in myplayerList
        vector<Player> myplayerList;  //list of
        vector<Player> turnplayerList;//list of
        vector<int> devDeck;
        Gameboard board;
        int numPlayers;
        int currDiceRoll;
        Dev DevDeck;
        Player currentPlayer;

private:
        int clockID;
        multimap<int, Player> playerTurnList;

        };
#endif
