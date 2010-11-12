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
    for (vector<string>::iterator it = namesIn.begin(); it != namesIn.end(); it++)
    {
        Player player(*it);
        myplayerList.push_back(player);
    }

for (vector<Player>::iterator it = myplayerList.begin(); it != myplayerList.end(); it++) {
    (*it).PieceHand.cityPiece = 4;
    (*it).PieceHand.settlementPiece = 5;
    (*it).PieceHand.roadPiece = 13;
    (*it).CardHand.longestRoadCard = 0;
    (*it).CardHand.largestArmyCard = 0;
    (*it).DevHand.knightCard = 0;
    (*it).DevHand.monopolyCard = 0;
    (*it).DevHand.roadBuildingCard = 0;
    (*it).DevHand.yearOfPlentyCard = 0;
    (*it).DevHand.progressCard = 0;
    (*it).DevHand.victoryPointCard = 0;

// initialize resource cards when they place their house
}
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

void Catan::placeSettlement(Player currPlayer, int vertNum){
    if (board.validSettle(currPlayer.turnNum, vertNum)==1){
        cout << "\nvertex is occupied, please choose another location\n";
        cin >> vertNum;
        placeSettlement(currPlayer, vertNum);
    }
    if (board.validSettle(currPlayer.turnNum, vertNum)==2){
        cout << "\nthere is already a building nearby, please choose another location\n";
        cin >> vertNum;
        placeSettlement(currPlayer, vertNum);
    }
    if (board.validSettle(currPlayer.turnNum, vertNum)==3){
        cout << "you have to build settlements adjacent to your road, please choose another location\n";
        cin >> vertNum;
        placeSettlement(currPlayer, vertNum);
    }
return;
}

void Catan::placeFirstSettlement(Player currPlayer, int vertNum){
    if (board.validSettle(currPlayer.turnNum, vertNum)==1){
        cout << "\nvertex is occupied, please choose another location\n";
        cin >> vertNum;
        placeFirstSettlement(currPlayer, vertNum);
    }
    else if (board.validSettle(currPlayer.turnNum, vertNum)==2){
        cout << "\nthere is already a building nearby, please choose another location\n";
        cin >> vertNum;
        placeFirstSettlement(currPlayer, vertNum);
    }
    else {
        board.setSettle(currPlayer.turnNum, vertNum);
        cout<<"settlement placed\n";
        return;
    }
}

void Catan::placeRoad(Player currPlayer, int edgeNum){
    if(board.validRoad(currPlayer.turnNum, edgeNum)==1){
        cout << "\nedge is occupied, please choose another location\n";
        cin >> edgeNum;
        placeRoad(currPlayer, edgeNum);
    }
    else {
       // cout<<"placing road\n";
        board.setRoad(currPlayer.turnNum, edgeNum);
        cout<<"road placed\n";
        return;
    }
}


string Catan::findLongestRoad() {
/*for (vector<Player>::iterator it = playerList.begin(); it != playerList.end(); it++) {
if ((((*it).CardHand).longestRoadCard) == 1);
// cout << (*it).getName();

}*/
    return "na";
}

//enum resourceType {BRICK, GRAIN, LUMBER, STONE, WOOL};
void trade(Player player1, Player player2) {
    int amountTrade;
    resourceType playerCard;
    string in;
    cout << player1.getName() << ", how many cards would you like to trade?" << endl;
    cin >> amountTrade;
    cout << player1.getName() << ", wants to trade" << amountTrade << "cards." << endl;
    for (int i = 0; i<amountTrade; i++) {
        cin >> in;
        if (in.compare("BRICK") == 0)
            playerCard = BRICK;
        else if (in.compare("GRAIN") == 0)
            playerCard == GRAIN;
        else if (in.compare("LUMBER") == 0)
            playerCard == LUMBER;
        else if (in.compare("STONE") == 0)
            playerCard == STONE;
        else if (in.compare("WOOL") == 0)
            playerCard == WOOL;
        cout << player1.getName() << ", wants to trade" << playerCard << endl;
        player1.recOut(playerCard);
        player2.recIn(playerCard);
    }

    cout << player2.getName()<< ", how many cards would you like to trade?" << endl;
    cin >> amountTrade;
    cout << player2.getName() << ", wants to trade" << amountTrade << "cards." << endl;
    for (int i = 0; i<amountTrade; i++) {
        cin >> in;
        if (in.compare("BRICK") == 0)
            playerCard = BRICK;
        else if (in.compare("GRAIN") == 0)
            playerCard == GRAIN;
        else if (in.compare("LUMBER") == 0)
            playerCard == LUMBER;
        else if (in.compare("STONE") == 0)
            playerCard == STONE;
        else if (in.compare("WOOL") == 0)
            playerCard == WOOL;

        cout << player2.getName() << ", wants to trade" << playerCard << endl;
        player2.recOut(playerCard);
        player1.recIn(playerCard);
    }
    cout << "Thank you for trading." << endl;

}

void Catan::firstYield(){
    terr tempTerrType;
    for(vector<HEXAGON>::iterator it=board.hexLayer.begin(); it != board.hexLayer.end(); it++) {
        tempTerrType = (*it).terrType;
        for (vector<VERTEX>::iterator it2=board.vertLayer.begin(); it2 != board.vertLayer.end(); it2++) {
            if ((*it2).occupiedBy == PLAYER0)
                myplayerList[0].addRec(tempTerrType);
            else if ((*it2).occupiedBy == PLAYER1)
                //add +1 resource of tempTerrType to Player1's CardHand
                myplayerList[1].addRec(tempTerrType);




        }
    }
}

//void Catan::yield(){

//}

//void Catan::decideTurn() {}


