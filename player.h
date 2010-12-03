// player.h
// player class for Virtual Catan

#ifndef _PLAYER_H
#define _PLAYER_H

#include <map>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <sys/time.h>
#include <vector>
using namespace std;

enum playerNum { PLAYER0, PLAYER1, PLAYER2, PLAYER3, NOONE};
enum pieceType {SETTLEMENT, CITY, ROAD, BANDIT};
enum resourceType {BRICK, GRAIN, LUMBER, STONE, WOOL};
enum terr {HILLS, FIELD, FOREST, MOUNTAINS, PASTURE, DESERT};
enum devType { SOLDIER, VICTORYPOINT, MONOPOLY, ROAD_BUILDING, YEAR_OF_PLENTY };

struct Piece{
int cityPiece;
int settlementPiece;
int roadPiece;
};

struct Resources{
    int stone;
    int grain;
    int lumber;
    int wool;
    int brick;
};

struct Dev {
    int soldierCard;
    int victoryPointCard;
    int monopolyCard;
    int roadBuildingCard;
    int yearOfPlentyCard;
    int size;
};

class Player{

public:

                         ////////MEMBER FUNCTIONS//////////

Player();
Player(string name);
int getScore();
int makeRoll();
int pickRandCard();
int getAmountPieces(Player player);
void addRec(terr terrType);
void promptPlayer();
void recIn(resourceType playerCard);
void recOut(resourceType playerCard);
void setScore(int currentScore);
void setTurn(playerNum num);
void printHand();
playerNum getTurn();
string getName();


                       ////////DATA MEMBERS//////////


    bool hasLongestRoad;
    bool hasLargestArmy;
    resourceType resource;
    int devType;
    int numRoads;  //for longest road
    int victoryPoints;
    Dev DevHand;
    Dev DevPlayed;
    Dev buffer;
    Piece PieceHand;
    Resources ResourceHand;
    vector<int> portsOwned;


private:
playerNum turnNum;
int nextPlayerTurn;
string playerName;

};



/////Dev Card stuff
//



#endif
