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
using namespace std;

enum playerNum { PLAYER0, PLAYER1, PLAYER2, PLAYER3, NOONE};
enum pieceType {SETTLEMENT, CITY, ROAD, BANDIT};
enum resourceType {BRICK, GRAIN, LUMBER, STONE, WOOL};
enum terr {HILLS, FIELD, FOREST, MOUNTAINS, PASTURE, DESERT};
enum devType { KNIGHT, MONOPOLY, PROGRESS, ROAD_BUILDING, YEAR_OF_PLENTY };

struct Piece{
int cityPiece;
int settlementPiece;
int roadPiece;
bool robberPiece;

};

struct Resources{
    int stone;
    int grain;
    int lumber;
    int wool;
    int brick;
};

struct Dev {
    int knightCard;
    int monopolyCard;
    int roadBuildingCard;
    int yearOfPlentyCard;
    int victoryPointCard;
    int progressCard;
};

class Player{

public:
Player();
Player(string name);

bool longestRoadCard;
bool largestArmyCard;
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
resourceType resource;
int devType;
Dev DevHand;
Piece PieceHand;
Resources ResourceHand;


private:
playerNum turnNum;
int nextPlayerTurn;
int individualScore;
string playerName;

};



/////Dev Card stuff
//



#endif
