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
using namespace std;


enum playerNum { PLAYER0, PLAYER1, PLAYER2, PLAYER3, PLAYER4};
enum pieceType {SETTLEMENT, CITY, ROAD, BANDIT};
enum cardType { BRICK, GRAIN, LUMBER, STONE, WOOL, KNIGHT, MONOPOLY, PROGRESS, ROAD_BUILDING,
YEAR_OF_PLENTY };

struct PieceHand1{
int cityPiece;
int settlementPiece;
int roadPiece;
bool robberPiece;

};

struct CardHand1{
bool longestRoadCard;
bool largestArmyCard;
int victoryPointCard;
int progressCard;
int stoneCard;
int grainCard;
int lumberCard;
int woolCard;
int brickCard;
int knightCard;
int monopolyCard;
int roadBuildingCard;
int yearOfPlentyCard;
};

class Player{

public:
Player();
Player(string name);

int makeRoll();
int pickRandCard();
void promptPlayer();
int getAmountPieces(Player player);
void setScore(int currentScore);
int getScore();
unsigned int playerNum;
string getName();
PieceHand1 PieceHand;
CardHand1 CardHand;


private:
int nextPlayerTurn;
int numberTurn;
int PlayerID;
int roll;
int individualScore;
string playerName;

};








#endif
