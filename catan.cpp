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
    numPlayers = numPlayersIn;

    pair<map<int, Player>::iterator, bool> ret;
    vector<Player>::iterator it2;

    for (vector<string>::iterator it = namesIn.begin(); it != namesIn.end(); it++)
    {
        Player player(*it);
        myplayerList.push_back(player);
        it2++;
    }


/*for (vector<Player>::iterator it = myplayerList.begin(); it != myplayerList.end(); it++) {
    (*it).PieceHand.cityPiece = 4;
    (*it).PieceHand.settlementPiece = 5;
    (*it).PieceHand.roadPiece = 13;
    (*it).CardHand.longestRoadCard = 0;
    (*it).CardHand.largestArmyCard = 0;
    (*it).CardHand.progressCard = 0;
    (*it).CardHand.monopolyCard = 0;
    (*it).CardHand.knightCard = 0;
    (*it).CardHand.yearOfPlentyCard = 0;
    (*it).CardHand.roadBuildingCard = 0;*/

// initialize resource cards when they place their house
}



string Catan::findLongestRoad() {
/*for (vector<Player>::iterator it = playerList.begin(); it != playerList.end(); it++) {
if ((((*it).CardHand).longestRoadCard) == 1);
// cout << (*it).getName();

}*/
    return "na";
}

void Catan::InitializeHand() {
for (vector<Player>::iterator it = myplayerList.begin(); it != myplayerList.end(); it++) {

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
