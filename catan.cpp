// catan.cpp
// implementation for catan class

#include "catan.h"
#include <stdio.h>
#include <map>
#include <vector>
#include <sys/time.h>

using namespace std;




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

    //NOTE: gameboard is implicity initialized here
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

    if(board.validRoad(currPlayer.turnNum, edgeNum)==3){
        cout << "\nyou must build next to an existing road or settlement, please choose another location\n";
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

void Catan::trade(Player player1, Player player2) {
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
            playerCard = GRAIN;
        else if (in.compare("LUMBER") == 0)
            playerCard = LUMBER;
        else if (in.compare("STONE") == 0)
            playerCard = STONE;
        else if (in.compare("WOOL") == 0)
            playerCard = WOOL;
        else{
            cout<<"not a valid option\n";
        trade(player1, player2);
        return;
        }
        cout << player1.getName() << ", wants to trade" << playerCard << endl;
        player1.recOut(playerCard);
        player2.recIn(playerCard);
        return;
    }

    cout << player2.getName()<< ", how many cards would you like to trade?" << endl;
    cin >> amountTrade;
    cout << player2.getName() << ", wants to trade" << amountTrade << "cards." << endl;
    for (int i = 0; i<amountTrade; i++) {
        cin >> in;
        if (in.compare("BRICK") == 0)
            playerCard = BRICK;
        else if (in.compare("GRAIN") == 0)
            playerCard = GRAIN;
        else if (in.compare("LUMBER") == 0)
            playerCard = LUMBER;
        else if (in.compare("STONE") == 0)
            playerCard = STONE;
        else if (in.compare("WOOL") == 0)
            playerCard = WOOL;

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
                turnplayerList[0].addRec(tempTerrType);
            else if ((*it2).occupiedBy == PLAYER1)    //add +1 resource of tempTerrType to Player1's CardHand
                turnplayerList[1].addRec(tempTerrType);
            else if ((*it2).occupiedBy == PLAYER2)
                turnplayerList[2].addRec(tempTerrType);
            else if ((*it2).occupiedBy == PLAYER3)
                turnplayerList[3].addRec(tempTerrType);
        }
    }
}

int Catan::diceRoll(){
    int dice1, dice2;
    timeval Time;
    gettimeofday(&Time, NULL);
    srand(Time.tv_usec);
    dice1 = 1 + rand()%6; // rolls first die, number between 1 and 6;
    dice2 = 1 + rand()%6;
    int i = (dice1+dice2);
    return i;
}

void Catan::yield(){
    terr tempTerrType;
    currDiceRoll = diceRoll();
    for(vector<HEXAGON>::iterator it=board.hexLayer.begin(); it != board.hexLayer.end(); it++) {
        tempTerrType = (*it).terrType;
        if(currDiceRoll == (*it).yieldNum){
            for (vector<VERTEX>::iterator it2=board.vertLayer.begin(); it2 != board.vertLayer.end(); it2++){
                if ((*it2).occupiedBy == PLAYER0)         //add +1 resource of tempTerrType to Player0's CardHand
                    turnplayerList[0].addRec(tempTerrType);
                else if ((*it2).occupiedBy == PLAYER1)    //add +1 resource of tempTerrType to Player1's CardHand
                    turnplayerList[1].addRec(tempTerrType);
                else if ((*it2).occupiedBy == PLAYER2)    //add +1 resource of tempTerrType to Player2's CardHand
                    turnplayerList[2].addRec(tempTerrType);
                else if ((*it2).occupiedBy == PLAYER3)    //add +1 resource of tempTerrType to Player3's CardHand
                    turnplayerList[3].addRec(tempTerrType);
            }
        }
    }

    //check the victory points.
}

//void Catan::decideTurn() {}
