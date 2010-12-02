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

    Catan(bool fromNewGame);
    Catan(int numPlayersIn, vector<string> namesIn, bool fromNewGame);     //initialize for NewGame();
    void saveGame();                                     //implemented Save Game feature
    void loadGame();
    void placeSettlement(Player& currPlayer, int vertNum);//regular placement of settlement on the gameboard
    void placeFirstSettlement(Player& currPlayer, int &vertNum);//placement of settlement during the first turn
    void placeRoad(Player currPlayer, int edgeNum);      //player's placement of road on the gameboard
    void placeCity(Player currPlayer, int vertNum);
    void trade();           //function called during the Turn() function in main
    void portTrade();
    void trade4_1();
    void firstYield();      //happens only during the first turn of the game, giving recourses to all players
    void yield(int rollNum);     //happens at beginning(end) of every turn, gives players recourses and checks for winner
    void decideOrder();     //used to determine order of players
    void endTurn();         //ends current players turn
    void buildSettle();     //builds a player's settlement for resources
    void buildRoad();       //builds a player's road for resources
    void upCity();          //upgrades a player's settlement to a city for resources
    int currentTime(int clockID);
    int diceRoll(Player currPlayer);                                      //Dice Roll for regular turns, returns value 2-12
    playerNum intToNum(int);
    string findLongestRoad();                            //unimplemented determination of which player has "Longest Road"
    Player * goesFirst(vector<Player> playerList);
    Player declareWinner(int playerID);
    void drawfromDevDeck();
    void devIn(devType dt);
    void devOut(devType dt);
    bool sufficientRec(string in);

                       ////////DATA MEMBERS//////////

        vector<Player> myplayerList;  //list of pointers to players in game
        vector<Player> turnplayerList;//list of pointers to players, ordered by turn
        Gameboard board;              //datastructure in which game is played upon
        int numPlayers;               //number of players in turnplayer list
        int currentPlayer;            //integer value (in relation to Player enum) of current player
        bool endGame;                 //ends the gamestate loop
        Dev DevDeck;                  //deck that contains un-drawn dev cards

private:
        int clockID;
        };
#endif
