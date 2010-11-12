// catan.cpp
// implementation for catan class

#include "catan.h"
#include <stdio.h>
#include <map>
#include <vector>
using namespace std;

Catan::Catan(){
// do nothing.
}

Catan::Catan(int numPlayersIn, vector<string> namesIn) {
int currentPlayerRoll, counter = 0;
pair<map<int, Player>::iterator, bool> ret;

for (vector<string>::iterator it = namesIn.begin(); it != namesIn.end(); it++)
{
Player player(*it);
currentPlayerRoll = player.makeRoll();
playerTurnList.insert(pair<int, Player>(currentPlayerRoll, (*it)));
}
vector<Player>::iterator it;
for (map<int, Player>::iterator it2 = playerTurnList.begin(); it2 != playerTurnList.end(); it2++) {
(it2->second).playerNum = (numPlayersIn - counter);
playerList.insert(it, it2->second);
counter++;
}

for (vector<Player>::iterator it = playerList.begin(); it !=
playerList.end(); it++) {
(*it).PieceHand.cityPiece = 4;
(*it).PieceHand.settlementPiece = 5;
(*it).PieceHand.roadPiece = 13;
(*it).CardHand.longestRoadCard = 0;
(*it).CardHand.largestArmyCard = 0;
(*it).CardHand.progressCard = 0;
(*it).CardHand.monopolyCard = 0;
(*it).CardHand.knightCard = 0;
(*it).CardHand.yearOfPlentyCard = 0;
(*it).CardHand.roadBuildingCard = 0;

// initialize resource cards when they place their house
}
}


string Catan::findLongestRoad() {
/*for (vector<Player>::iterator it = playerList.begin(); it != playerList.end(); it++) {
if ((((*it).CardHand).longestRoadCard) == 1);
// cout << (*it).getName();

}*/
    return "na";
}

void Catan::InitializeHand() {
for (vector<Player>::iterator it = playerList.begin(); it != playerList.end(); it++) {

// for loop ( 3 times )
/*switch() {
case 0:
((*it)->CardHand.brickCard)++;
break;
case 1:
((*it)->CardHand.grainCard)++;
break;
case 2:
((*it)->CardHand.lumberCard)++;
break;
case 3:
((*it)->CardHand.stoneCard)++;
break;
case 4:
((*it)->CardHand.woolCard)++;
break;

}*/

}
}
