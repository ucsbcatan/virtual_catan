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
    void saveGame();   //implemented Save Game feature
    void loadGame();   //implemented Load Game feature
    void placeSettlement(Player& currPlayer, int vertNum);//regular placement of settlement on the gameboard
    void placeFirstSettlement(Player& currPlayer, int &vertNum);//placement of settlement during the first turn
    void placeRoad(Player currPlayer, int edgeNum);      //player's placement of road on the gameboard
    void placeCity(Player& currPlayer, int vertNum);     //repaces one of player's settlements with a city
    void trade();           //function called during the Turn() function in main when you want to trade with a player
    void portTrade();       //fucntion called when player wants to trade with one of their ports
    void trade4_1();        //function called when player wants to trade with the "deck" by trading in 4 of one card for 1 of another
    void firstYield();      //happens only during the first turn of the game, giving recourses to all players
    void yield(int rollNum);     //happens at beginning(end) of every turn, gives players recourses and checks for winner
    void decideOrder();     //used to determine order of players
    void endTurn();         //ends current players turn
    void buildSettle();     //builds a player's settlement for resources
    void buildRoad();       //builds a player's road for resources
    void upCity();          //upgrades a player's settlement to a city for resources
    int currentTime(int clockID);
    int diceRoll(Player currPlayer); //Dice Roll for regular turns, returns value 2-12
    playerNum intToNum(int);//converts integers to playerNum
    void setLongestRoad();  //at the beginnin of every Turn(), check which player has most roads and give them the honor
    void setLargestArmy();  //check which player has the most soldier cards in their DevPlayed and give them the honor
    Player * goesFirst(vector<Player> playerList);
    void drawfromDevDeck(); //
    void devIn(devType dt); //brings dev card from devdeck to player's buffer
    void devIn2Hand(devType dt);
    void devOut(devType dt);//brings dev card from player's devhand to devplayed
    bool sufficientRec(string in); //makes sure player has enough resources for building road, settlement, city, or devcard
    bool checksForWinner(); //called at the end of turn, checks to see if their is a winner with 8 points
    void declareWinner(Player player); //if checksForWinner is true, this function announces winner and exits the game
    void check7(int);
    void movingBandit();



                       ////////DATA MEMBERS//////////

        vector<Player> myplayerList;  //list of pointers to players in game
        vector<Player> turnplayerList;//list of pointers to players, ordered by turn
        Gameboard board;              //datastructure in which game is played upon
        int numPlayers;               //number of players in turnplayer list
        int currentPlayer;            //integer value (in relation to Player enum) of current player
        bool endGame;                 //ends the gamestate loop
        Dev DevDeck;                  //deck that contains un-drawn dev cards
//        playerNum hasLR;              //keeps track of which player that has Longest Road honor
//        playerNum hasLA;              //keeps track of who has Largest Army

private:
        int clockID;
        };
#endif
