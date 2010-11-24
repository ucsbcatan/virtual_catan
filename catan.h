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

//This class holds all of the information about the current game being played, such as the list of players, the
//gameboard, and the current score.

class Catan {
public:
                     ////////MEMBER FUNCTIONS//////////

    Catan(int numPlayersIn, vector<string> namesIn);     //initialize for NewGame();
    void saveGame();                                     //unimplemented Save Game feature
    void placeSettlement(Player currPlayer, int vertNum);//regular placement of settlement on the gameboard
    void placeFirstSettlement(Player currPlayer, int &vertNum);//placement of settlement during the first turn
    void placeRoad(Player currPlayer, int edgeNum);      //player's placement of road on the gameboard
    void placeCity(Player currPlayer, int vertNum);
    void trade();           //function called during the Turn() function in main
    void firstYield();      //happens only during the first turn of the game, giving recourses to all players
    void yield(int rollNum);     //happens at beginning(end) of every turn, gives players recourses and checks for winner
    void decideOrder();     //used to determine order of players
    void endTurn();         //ends current players turn
    void buildSettle();     //builds a player's settlement for resources
    void buildRoad();       //builds a player's road for resources
    void upCity();          //upgrades a player's settlement to a city for resources
    int currentScore();
    int currentTime(int clockID);
    int diceRoll(Player currPlayer);                                      //Dice Roll for regular turns, returns value 2-12
    int getScore();
    playerNum intToNum(int);
    string findLongestRoad();                            //unimplemented determination of which player has "Longest Road"
    Player * goesFirst(vector<Player> playerList);
    Player declareWinner(int playerID);

                       ////////DATA MEMBERS//////////

        playerNum currPlayer;         //keeps track of the current player in myplayerList
        vector<Player> myplayerList;  //list of pointers to players in game
        vector<Player> turnplayerList;//list of pointers to players, ordered by turn
        vector<int> devDeck;
        Gameboard board;
        int numPlayers;
        int currDiceRoll;
        Dev DevDeck;
        int currentPlayer;

private:
        int clockID;
        multimap<int, Player> playerTurnList;

        };
#endif
