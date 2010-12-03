// catan.cpp
// implementation for catan class

#include "catan.h"
#include <stdio.h>
#include <map>
#include <vector>
#include <sys/time.h>
#include <fstream>
#include <sstream>
#include "player.h"
#include "timeFunc.h"
using namespace std;


Catan::Catan(bool fromNewGame){

    if (!fromNewGame){
       Gameboard newboard(false);
       board = newboard;
   }
    loadGame();
}

Catan::Catan(int numPlayersIn, vector<string> namesIn, bool fromNewGame) {
    if(fromNewGame){
        Gameboard newboard(true);
        board = newboard;
    }
    numPlayers = numPlayersIn;

    for (int i=0;i<(int)namesIn.size();i++)
    {
        Player player(namesIn[i]);
        myplayerList.push_back(player);
    }

    for (vector<Player>::iterator it = myplayerList.begin(); it != myplayerList.end(); it++) {
        (*it).PieceHand.cityPiece = 4;
        (*it).PieceHand.settlementPiece = 5;
        (*it).PieceHand.roadPiece = 13;
        (*it).DevHand.soldierCard = 0;
        (*it).DevHand.monopolyCard = 0;
        (*it).DevHand.roadBuildingCard = 0;
        (*it).DevHand.yearOfPlentyCard = 0;
        (*it).DevHand.victoryPointCard = 0;
        (*it).DevPlayed.soldierCard = 0;
        (*it).DevPlayed.monopolyCard = 0;
        (*it).DevPlayed.roadBuildingCard = 0;
        (*it).DevPlayed.yearOfPlentyCard = 0;
        (*it).DevPlayed.victoryPointCard = 0;
        (*it).ResourceHand.stone=0;
        (*it).ResourceHand.grain=0;
        (*it).ResourceHand.lumber=0;
        (*it).ResourceHand.wool=0;
        (*it).ResourceHand.brick=0;

    }

    //DevDeck
    DevDeck.soldierCard = 14;
    DevDeck.victoryPointCard = 5;
    DevDeck.monopolyCard = 1;
    DevDeck.roadBuildingCard = 1;
    DevDeck.yearOfPlentyCard = 1;
    DevDeck.size = 22;

}

void Catan::saveGame(){
    ofstream myfile;
    myfile.open ("save.dat");

    //print numPlayers
    myfile << numPlayers;
    myfile << "\n";

    //print player names
    for (vector<Player>::iterator k =turnplayerList.begin(); k!=turnplayerList.end(); k++){
        myfile << (*k).getName() << " ";
        }
    myfile << "\n";

    //print number of current player
    myfile << currentPlayer;
    myfile << "\n";

    //print number of cards in DevDeck
    myfile << DevDeck.soldierCard << " ";
    myfile << DevDeck.victoryPointCard << " ";
    myfile << DevDeck.monopolyCard << " ";
    myfile << DevDeck.roadBuildingCard << " ";
    myfile << DevDeck.yearOfPlentyCard << " ";
    myfile << DevDeck.size << " ";
    myfile << "\n";

    //printing out gameboard information

    //hexlayer info
    for (int i=0; i<19; i++){
        myfile << board.hexLayer[i].terrType << " ";
        if (board.hexLayer[i].hasBandit==false)
            myfile <<"0 ";
        else
            myfile<<"1 ";
        myfile << board.hexLayer[i].yieldNum;
        myfile << "\n";
    }

    //vertlayer info
    for (int i=0; i<54; i++){
        myfile << board.vertLayer[i].occupiedBy << " ";
        myfile << board.vertLayer[i].occByType;
        myfile << "\n";
    }

    //edgelayer info
    for (int i=0; i<72; i++){
        myfile << board.edgeLayer[i].occupiedBy;
        myfile << "\n";
    }

    //yieldNums info
    myfile << board.yieldNums[0].num << " ";
    myfile << board.yieldNums[0].hex1;
    myfile << "\n";
    for(int i=1; i<9; i++){
        myfile << board.yieldNums[i].num<< " ";
        myfile << board.yieldNums[i].hex1<< " ";
        myfile << board.yieldNums[i].hex2<< " ";
        myfile << "\n";
    }
    myfile << board.yieldNums[9].num << " ";
    myfile << board.yieldNums[9].hex1;
    myfile << "\n";

    //ports info
    for (int i=0; i<9; i++){
        myfile << board.ports[i].loc1 << " ";
        myfile << board.ports[i].loc2 << " ";
        myfile << board.ports[i].type << " ";
        myfile << board.ports[i].player << " ";
        myfile <<"\n";
    }

    //banditLoc
    myfile << board.getBanditLoc();
    myfile <<"\n";

    //Player info
    for (vector<Player>::iterator k =turnplayerList.begin(); k!=turnplayerList.end(); k++){
        //print player's resources
        myfile << (*k).ResourceHand.stone << " ";
        myfile << (*k).ResourceHand.grain << " ";
        myfile << (*k).ResourceHand.lumber << " ";
        myfile << (*k).ResourceHand.wool << " ";
        myfile << (*k).ResourceHand.brick << " ";
        myfile << "\n";

        //print player's victory points
        myfile << (*k).victoryPoints << "\n";

        //print player's dev cards played
        myfile << (*k).DevPlayed.soldierCard << " ";
        myfile << (*k).DevPlayed.monopolyCard << " ";
        myfile << (*k).DevPlayed.roadBuildingCard << " ";
        myfile << (*k).DevPlayed.yearOfPlentyCard << " ";
        myfile << (*k).DevPlayed.victoryPointCard << " ";
        myfile << "\n";

        //print player's dev cards in hand
        myfile << (*k).DevHand.soldierCard << " ";
        myfile << (*k).DevHand.monopolyCard << " ";
        myfile << (*k).DevHand.roadBuildingCard << " ";
        myfile << (*k).DevHand.yearOfPlentyCard << " ";
        myfile << (*k).DevHand.victoryPointCard << " ";
        myfile << "\n";

        //print player's pieceHand
        myfile << (*k).PieceHand.cityPiece << " ";
        myfile << (*k).PieceHand.settlementPiece << " ";
        myfile << (*k).PieceHand.roadPiece << " ";
        myfile << "\n";

        //print player's honors (longest whatever)
        if ((*k).hasLongestRoad==false)
            myfile <<"0 ";
        else
            myfile<<"1 ";

        if ((*k).hasLargestArmy==true)
            myfile <<"0";
        else
            myfile<<"1";

        myfile << "\n";

        //print player's turnNum
        myfile << (*k).getTurn();
        myfile << "\n";

        //print player's vector of portsOwned
        for (vector<int>::iterator i =(*k).portsOwned.begin(); i!=(*k).portsOwned.end(); i++){
            myfile<< *i <<" ";
        }
        myfile<<"\n";
    }

    myfile.close();
    return;
}

void Catan::loadGame(){
    ifstream infile;
    infile.open("save.dat");
    if(!infile.good()){
        infile.close();
        return;
    }
    string str, word;
    int val;
    bool boolean;

    int counter=1;
    int dickslang=0;

    while(infile.good() && getline(infile,str)){
        stringstream ss(str);

        //read and assign numPlayers
        if(counter==1){
            while(ss.good()){
               ss >> val;
               numPlayers = val;
           }
        }

        //read and create turnplayerList with player names
        else if(counter==2){
            int i = numPlayers;
            while(i!=0){
                ss >> word;
                Player player(word);
                turnplayerList.push_back(player);
                i--;
            }
        }

        //read and assign currentPlayer integer
        else if(counter==3){
            while(ss.good()){
                ss >> val;
                currentPlayer = val;
            }
        }

        //read and initialize DevDeck in Catan class
        else if(counter==4){
            while(ss.good()){
                ss >> val;
                if (dickslang==0)
                    DevDeck.soldierCard = val;
                else if (dickslang==1)
                    DevDeck.victoryPointCard = val;
                else if (dickslang==2)
                    DevDeck.monopolyCard = val;
                else if (dickslang==3)
                    DevDeck.roadBuildingCard = val;
                else if (dickslang==4)
                    DevDeck.yearOfPlentyCard =  val;
                else if (dickslang==5)
                    DevDeck.size = val;
                dickslang++;
            }
            dickslang=0;
        }

        //read and initialize the hexLayer
        else if((counter>=5)&&(counter<=23)){
            while(ss.good()){
                if(dickslang==0){
                    ss >> val;
                    if(val==0)
                        board.hexLayer[(counter-5)].terrType = HILLS;
                    else if(val==1)
                        board.hexLayer[(counter-5)].terrType = FIELD;
                    else if(val==2)
                        board.hexLayer[(counter-5)].terrType = FOREST;
                    else if(val==3)
                        board.hexLayer[(counter-5)].terrType = MOUNTAINS;
                    else if(val==4)
                        board.hexLayer[(counter-5)].terrType = PASTURE;
                    else if(val==5)
                        board.hexLayer[(counter-5)].terrType = DESERT;
                }
                else if(dickslang==1){
                    ss >> boolean;
                    board.hexLayer[(counter-5)].hasBandit = boolean;
                }
                else if(dickslang==2){
                    ss >> val;
                    board.hexLayer[(counter-5)].yieldNum = val;
                }
                dickslang++;
            }
            dickslang=0;
        }

        //read and initialize the vertLayer
        else if((counter>=24) && (counter<=77)){
            while(ss.good()) {
                if (dickslang==0) {
                    ss >> val;
                    if (val==0)
                        board.vertLayer[counter-24].occupiedBy = PLAYER0;
                    else if (val==1)
                        board.vertLayer[counter-24].occupiedBy = PLAYER1;
                    else if (val==2)
                        board.vertLayer[counter-24].occupiedBy = PLAYER2;
                    else if (val==3)
                        board.vertLayer[counter-24].occupiedBy = PLAYER3;
                    else if (val==4)
                        board.vertLayer[counter-24].occupiedBy = NOONE;

                }
                else if (dickslang==1){
                    ss >> val;
                    board.vertLayer[counter-24].occByType = val;
                }
                dickslang++;
            }
            dickslang = 0;
        }


        // read and initialize edgeLayer
        else if ((counter>=78) && (counter <= 149)) {
            while(ss.good()) {
                ss >> val;
                if (val==0)
                    board.edgeLayer[counter-78].occupiedBy = PLAYER0;
                else if (val==1)
                    board.edgeLayer[counter-78].occupiedBy = PLAYER1;
                else if (val==2)
                    board.edgeLayer[counter-78].occupiedBy = PLAYER2;
                else if (val==3)
                    board.edgeLayer[counter-78].occupiedBy = PLAYER3;
                else if (val==4)
                    board.edgeLayer[counter-78].occupiedBy = NOONE;
            }
        }

        //read and initialize yieldNums vector
        else if(counter==150){
            while(ss.good()){
                ss >> val;
                if (dickslang==0){
                    board.yieldNums[0].num = val;
                }
                else if (dickslang==1){
                    board.yieldNums[0].hex1 = val;
                }

                dickslang++;
            }
            dickslang=0;
        }

        else if( (counter>=151) && (counter<=158) ){
            while(ss.good()){
                ss >> val;
                if (dickslang==0)
                    board.yieldNums[(counter-150)].num = val;
                else if (dickslang==1)
                    board.yieldNums[(counter-150)].hex1 = val;
                else if (dickslang==1)
                    board.yieldNums[(counter-150)].hex1 = val;

                dickslang++;
            }
            dickslang=0;
        }
        else if(counter==159){
            while(ss.good()){
                ss >> val;
                if (dickslang==0)
                    board.yieldNums[9].num = val;
                else if (dickslang==1)
                    board.yieldNums[9].hex1 = val;

                dickslang++;
            }
            dickslang=0;
        }

        //read and initialize the ports
        else if ((counter>=160) && (counter<=168)){
            while(ss.good()){
                ss >> val;
                if (dickslang==0)
                    board.ports[(counter-160)].loc1 = val;
                else if (dickslang==1)
                    board.ports[(counter-160)].loc2 = val;
                else if (dickslang==2)
                    board.ports[(counter-160)].type = val;
                else if (dickslang==3){
                    if (val==0)
                        board.ports[(counter-160)].player = PLAYER0;
                    else if (val==1)
                        board.ports[(counter-160)].player = PLAYER1;
                    else if (val==2)
                        board.ports[(counter-160)].player = PLAYER2;
                    else if (val==3)
                        board.ports[(counter-160)].player = PLAYER3;
                    else if (val==4)
                        board.ports[(counter-160)].player = NOONE;
                    }

                dickslang++;
            }
            dickslang=0;
        }

        //read and initialize banditLoc
        else if(counter==169){
            while(ss.good()){
                ss >> val;
                board.setBanditLoc(val);
            }
        }


        //PLAYER 0-2's information
        else if((counter>=170) && (counter <= 193)){
                //PLAYER0's ResourceHand
                if(counter==(170)){
                    while(ss.good()){
                        ss >> val;
                        if(dickslang==0)
                            turnplayerList[0].ResourceHand.stone = val;
                        else if(dickslang==1)
                            turnplayerList[0].ResourceHand.grain = val;
                        else if(dickslang==2)
                            turnplayerList[0].ResourceHand.lumber = val;
                        else if(dickslang==3)
                            turnplayerList[0].ResourceHand.wool = val;
                        else if(dickslang==4)
                            turnplayerList[0].ResourceHand.brick = val;

                        dickslang++;
                    }
                    dickslang=0;
                }
                //PLAYER0's VictoryPoints
                else if(counter==171){
                    while(ss.good()){
                        ss >> val;
                        turnplayerList[0].victoryPoints = val;
                    }
                }
                //PLAYER0's DevPlayed
                else if(counter==172){
                    while(ss.good()){
                        ss >> val;
                        if(dickslang==0)
                            turnplayerList[0].DevPlayed.soldierCard = val;
                        else if(dickslang==1)
                            turnplayerList[0].DevPlayed.victoryPointCard = val;
                        else if(dickslang==2)
                            turnplayerList[0].DevPlayed.monopolyCard = val;
                        else if(dickslang==3)
                            turnplayerList[0].DevPlayed.roadBuildingCard = val;
                        else if(dickslang==4)
                            turnplayerList[0].DevPlayed.yearOfPlentyCard = val;
                        else if(dickslang==5)
                            turnplayerList[0].DevPlayed.size = val;

                        dickslang ++;
                    }
                    dickslang = 0;
                }
                //PLAYER0's DevHand
                else if(counter==173){
                    while(ss.good()){
                        ss >> val;
                        if(dickslang==0)
                            turnplayerList[0].DevHand.soldierCard = val;
                        else if(dickslang==1)
                            turnplayerList[0].DevHand.victoryPointCard = val;
                        else if(dickslang==2)
                            turnplayerList[0].DevHand.monopolyCard = val;
                        else if(dickslang==3)
                            turnplayerList[0].DevHand.roadBuildingCard = val;
                        else if(dickslang==4)
                            turnplayerList[0].DevHand.yearOfPlentyCard = val;
                        else if(dickslang==5)
                            turnplayerList[0].DevHand.size = val;

                        dickslang ++;
                    }
                    dickslang = 0;
                }
                //PLAYER0's PieceHand
                else if(counter==174){
                    while(ss.good()){
                        ss >> val;
                        if(dickslang==0)
                            turnplayerList[0].PieceHand.cityPiece = val;
                        else if(dickslang==1)
                            turnplayerList[0].PieceHand.settlementPiece = val;
                        else if(dickslang==2)
                            turnplayerList[0].PieceHand.roadPiece = val;

                        dickslang++;
                    }
                    dickslang=0;
                }
                //PLAYER0's Honors
                else if(counter==175){
                    while(ss.good()){
                        ss >> boolean;
                        if(dickslang==0)
                            turnplayerList[0].hasLongestRoad = boolean;
                        if(dickslang==1)
                            turnplayerList[0].hasLargestArmy = boolean;

                        dickslang++;
                    }
                    dickslang=0;
                }

                //PLAYER0's Playerturn
                else if(counter==176){
                    while(ss.good()){
                        ss >> val;
                        if (val==0)
                            turnplayerList[0].setTurn(PLAYER0);
                        if (val==1)
                            turnplayerList[0].setTurn(PLAYER1);
                        if (val==2)
                            turnplayerList[0].setTurn(PLAYER2);
                        if (val==3)
                            turnplayerList[0].setTurn(PLAYER3);
                    }
                }
                //PLAYER0's portsOwned
                else if(counter==177){
                    while(ss.good()){
                        ss >> val;
                        turnplayerList[0].portsOwned.push_back(val);
                    }
                }


                //PLAYER1's ResourceHand
                if(counter==(178)){
                    while(ss.good()){
                        ss >> val;
                        if(dickslang==0)
                            turnplayerList[1].ResourceHand.stone = val;
                        else if(dickslang==1)
                            turnplayerList[1].ResourceHand.grain = val;
                        else if(dickslang==2)
                            turnplayerList[1].ResourceHand.lumber = val;
                        else if(dickslang==3)
                            turnplayerList[1].ResourceHand.wool = val;
                        else if(dickslang==4)
                            turnplayerList[1].ResourceHand.brick = val;

                        dickslang++;
                    }
                    dickslang=0;
                }
                //PLAYER1's VictoryPoints
                else if(counter==179){
                    while(ss.good()){
                        ss >> val;
                        turnplayerList[1].victoryPoints = val;
                    }
                }
                //PLAYER1's DevPlayed
                else if(counter==180){
                    while(ss.good()){
                        ss >> val;
                        if(dickslang==0)
                            turnplayerList[1].DevPlayed.soldierCard = val;
                        else if(dickslang==1)
                            turnplayerList[1].DevPlayed.victoryPointCard = val;
                        else if(dickslang==2)
                            turnplayerList[1].DevPlayed.monopolyCard = val;
                        else if(dickslang==3)
                            turnplayerList[1].DevPlayed.roadBuildingCard = val;
                        else if(dickslang==4)
                            turnplayerList[1].DevPlayed.yearOfPlentyCard = val;
                        else if(dickslang==5)
                            turnplayerList[1].DevPlayed.size = val;

                        dickslang ++;
                    }
                    dickslang = 0;
                }
                //PLAYER1's DevHand
                else if(counter==181){
                    while(ss.good()){
                        ss >> val;
                        if(dickslang==0)
                            turnplayerList[1].DevHand.soldierCard = val;
                        else if(dickslang==1)
                            turnplayerList[1].DevHand.victoryPointCard = val;
                        else if(dickslang==2)
                            turnplayerList[1].DevHand.monopolyCard = val;
                        else if(dickslang==3)
                            turnplayerList[1].DevHand.roadBuildingCard = val;
                        else if(dickslang==4)
                            turnplayerList[1].DevHand.yearOfPlentyCard = val;
                        else if(dickslang==5)
                            turnplayerList[1].DevHand.size = val;

                        dickslang ++;
                    }
                    dickslang = 0;
                }
                //PLAYER1's PieceHand
                else if(counter==182){
                    while(ss.good()){
                        ss >> val;
                        if(dickslang==0)
                            turnplayerList[1].PieceHand.cityPiece = val;
                        else if(dickslang==1)
                            turnplayerList[1].PieceHand.settlementPiece = val;
                        else if(dickslang==2)
                            turnplayerList[1].PieceHand.roadPiece = val;

                        dickslang++;
                    }
                    dickslang=0;
                }
                //PLAYER1's Honors
                else if(counter==183){
                    while(ss.good()){
                        ss >> boolean;
                        if(dickslang==0)
                            turnplayerList[1].hasLongestRoad = boolean;
                        if(dickslang==1)
                            turnplayerList[1].hasLargestArmy = boolean;

                        dickslang++;
                    }
                    dickslang=0;
                }

                //PLAYER1's Playerturn
                else if(counter==184){
                    while(ss.good()){
                        ss >> val;
                        if (val==0)
                            turnplayerList[1].setTurn(PLAYER0);
                        if (val==1)
                            turnplayerList[1].setTurn(PLAYER1);
                        if (val==2)
                            turnplayerList[1].setTurn(PLAYER2);
                        if (val==3)
                            turnplayerList[1].setTurn(PLAYER3);
                    }
                }

                //PLAYER1's portsOwned
                else if(counter==185){
                    while(ss.good()){
                        ss >> val;
                        turnplayerList[1].portsOwned.push_back(val);
                    }
                }


                //PLAYER2's ResourceHand
                if(counter==(186)){
                    while(ss.good()){
                        ss >> val;
                        if(dickslang==0)
                            turnplayerList[2].ResourceHand.stone = val;
                        else if(dickslang==1)
                            turnplayerList[2].ResourceHand.grain = val;
                        else if(dickslang==2)
                            turnplayerList[2].ResourceHand.lumber = val;
                        else if(dickslang==3)
                            turnplayerList[2].ResourceHand.wool = val;
                        else if(dickslang==4)
                            turnplayerList[2].ResourceHand.brick = val;

                        dickslang++;
                    }
                    dickslang=0;
                }
                //PLAYER2's VictoryPoints
                else if(counter==187){
                    while(ss.good()){
                        ss >> val;
                        turnplayerList[2].victoryPoints = val;
                    }
                }
                //PLAYER2's DevPlayed
                else if(counter==188){
                    while(ss.good()){
                        ss >> val;
                        if(dickslang==0)
                            turnplayerList[2].DevPlayed.soldierCard = val;
                        else if(dickslang==1)
                            turnplayerList[2].DevPlayed.victoryPointCard = val;
                        else if(dickslang==2)
                            turnplayerList[2].DevPlayed.monopolyCard = val;
                        else if(dickslang==3)
                            turnplayerList[2].DevPlayed.roadBuildingCard = val;
                        else if(dickslang==4)
                            turnplayerList[2].DevPlayed.yearOfPlentyCard = val;
                        else if(dickslang==5)
                            turnplayerList[2].DevPlayed.size = val;

                        dickslang ++;
                    }
                    dickslang = 0;
                }
                //PLAYER2's DevHand
                else if(counter==189){
                    while(ss.good()){
                        ss >> val;
                        if(dickslang==0)
                            turnplayerList[2].DevHand.soldierCard = val;
                        else if(dickslang==1)
                            turnplayerList[2].DevHand.victoryPointCard = val;
                        else if(dickslang==2)
                            turnplayerList[2].DevHand.monopolyCard = val;
                        else if(dickslang==3)
                            turnplayerList[2].DevHand.roadBuildingCard = val;
                        else if(dickslang==4)
                            turnplayerList[2].DevHand.yearOfPlentyCard = val;
                        else if(dickslang==5)
                            turnplayerList[2].DevHand.size = val;

                        dickslang ++;
                    }
                    dickslang = 0;
                }
                //PLAYER2's PieceHand
                else if(counter==190){
                    while(ss.good()){
                        ss >> val;
                        if(dickslang==0)
                            turnplayerList[2].PieceHand.cityPiece = val;
                        else if(dickslang==1)
                            turnplayerList[2].PieceHand.settlementPiece = val;
                        else if(dickslang==2)
                            turnplayerList[2].PieceHand.roadPiece = val;

                        dickslang++;
                    }
                    dickslang=0;
                }
                //PLAYER2's Honors
                else if(counter==191){
                    while(ss.good()){
                        ss >> boolean;
                        if(dickslang==0)
                            turnplayerList[2].hasLongestRoad = boolean;
                        if(dickslang==1)
                            turnplayerList[2].hasLargestArmy = boolean;

                        dickslang++;
                    }
                    dickslang=0;
                }

                //PLAYER2's Playerturn
                else if(counter==192){
                    while(ss.good()){
                        ss >> val;
                        if (val==0)
                            turnplayerList[2].setTurn(PLAYER0);
                        if (val==1)
                            turnplayerList[2].setTurn(PLAYER1);
                        if (val==2)
                            turnplayerList[2].setTurn(PLAYER2);
                        if (val==3)
                            turnplayerList[2].setTurn(PLAYER3);
                    }
                }

                //PLAYER2's portsOwned
                else if(counter==193){
                    while(ss.good()){
                        ss >> val;
                        turnplayerList[2].portsOwned.push_back(val);
                    }
                }
            }




        if(numPlayers==4){
            //PLAYER3's ResourceHand
            if(counter==(194)){
                while(ss.good()){
                    ss >> val;
                    if(dickslang==0)
                        turnplayerList[3].ResourceHand.stone = val;
                    else if(dickslang==1)
                        turnplayerList[3].ResourceHand.grain = val;
                    else if(dickslang==2)
                        turnplayerList[3].ResourceHand.lumber = val;
                    else if(dickslang==3)
                        turnplayerList[3].ResourceHand.wool = val;
                    else if(dickslang==4)
                        turnplayerList[3].ResourceHand.brick = val;

                    dickslang++;
                }
                dickslang=0;
            }
            //PLAYER3's VictoryPoints
            else if(counter==195){
                while(ss.good()){
                    ss >> val;
                    turnplayerList[3].victoryPoints = val;
                }
            }
            //PLAYER3's DevPlayed
            else if(counter==196){
                while(ss.good()){
                    ss >> val;
                    if(dickslang==0)
                        turnplayerList[3].DevPlayed.soldierCard = val;
                    else if(dickslang==1)
                        turnplayerList[3].DevPlayed.victoryPointCard = val;
                    else if(dickslang==2)
                        turnplayerList[3].DevPlayed.monopolyCard = val;
                    else if(dickslang==3)
                        turnplayerList[3].DevPlayed.roadBuildingCard = val;
                    else if(dickslang==4)
                        turnplayerList[3].DevPlayed.yearOfPlentyCard = val;
                    else if(dickslang==5)
                        turnplayerList[3].DevPlayed.size = val;

                    dickslang ++;
                }
                dickslang = 0;
            }
            //PLAYER3's DevHand
            else if(counter==197){
                while(ss.good()){
                    ss >> val;
                    if(dickslang==0)
                        turnplayerList[3].DevHand.soldierCard = val;
                    else if(dickslang==1)
                        turnplayerList[3].DevHand.victoryPointCard = val;
                    else if(dickslang==2)
                        turnplayerList[3].DevHand.monopolyCard = val;
                    else if(dickslang==3)
                        turnplayerList[3].DevHand.roadBuildingCard = val;
                    else if(dickslang==4)
                        turnplayerList[3].DevHand.yearOfPlentyCard = val;
                    else if(dickslang==5)
                        turnplayerList[3].DevHand.size = val;

                    dickslang ++;
                }
                dickslang = 0;
            }
            //PLAYER3's PieceHand
            else if(counter==198){
                while(ss.good()){
                    ss >> val;
                    if(dickslang==0)
                        turnplayerList[3].PieceHand.cityPiece = val;
                    else if(dickslang==1)
                        turnplayerList[3].PieceHand.settlementPiece = val;
                    else if(dickslang==2)
                        turnplayerList[3].PieceHand.roadPiece = val;

                    dickslang++;
                }
                dickslang=0;
            }
            //PLAYER3's Honors
            else if(counter==199){
                while(ss.good()){
                    ss >> boolean;
                    if(dickslang==0)
                        turnplayerList[3].hasLongestRoad = boolean;
                    if(dickslang==1)
                        turnplayerList[3].hasLargestArmy = boolean;

                    dickslang++;
                }
                dickslang=0;
            }

            //PLAYER3's Playerturn
            else if(counter==200){
                while(ss.good()){
                    ss >> val;
                    if (val==0)
                        turnplayerList[3].setTurn(PLAYER0);
                    if (val==1)
                        turnplayerList[3].setTurn(PLAYER1);
                    if (val==2)
                        turnplayerList[3].setTurn(PLAYER2);
                    if (val==3)
                        turnplayerList[3].setTurn(PLAYER3);
                }
            }

            //PLAYER3's portsOwned
            else if(counter==201){
                while(ss.good()){
                    ss >> val;
                    turnplayerList[3].portsOwned.push_back(val);
                }
            }
        }
        counter++;
    }
}

void Catan::placeSettlement(Player& currPlayer, int vertNum){
    if (board.validSettle(currPlayer.getTurn(), vertNum)==1){
        cout << "\nvertex is occupied, please choose another location\n";
        cin >> vertNum;
        placeSettlement(currPlayer, vertNum);
    }
    else if (board.validSettle(currPlayer.getTurn(), vertNum)==2){
        cout << "\nthere is already a building nearby, please choose another location\n";
        cin >> vertNum;
        placeSettlement(currPlayer, vertNum);
    }
    else if (board.validSettle(currPlayer.getTurn(), vertNum)==3){
        cout << "you have to build settlements adjacent to your road, please choose another location\n";
        cin >> vertNum;
        placeSettlement(currPlayer, vertNum);
    }
    else {
        board.setSettle(currPlayer.getTurn(), vertNum);
        if ((vertNum==0)||(vertNum==1)){
            board.ports[0].player=currPlayer.getTurn();
            currPlayer.portsOwned.push_back(0);
        }
        else if ((vertNum==3)||(vertNum==4)){
            board.ports[1].player=currPlayer.getTurn();
            currPlayer.portsOwned.push_back(1);
        }
        else if ((vertNum==14)||(vertNum==15)){
            board.ports[2].player=currPlayer.getTurn();
            currPlayer.portsOwned.push_back(2);
        }
        else if ((vertNum==26)||(vertNum==37)){
            board.ports[3].player=currPlayer.getTurn();
            currPlayer.portsOwned.push_back(3);
        }
        else if ((vertNum==46)||(vertNum==45)){
            board.ports[4].player=currPlayer.getTurn();
            currPlayer.portsOwned.push_back(4);
        }
        else if ((vertNum==51)||(vertNum==50)){
            board.ports[5].player=currPlayer.getTurn();
            currPlayer.portsOwned.push_back(5);
        }
        else if ((vertNum==48)||(vertNum==47)){
            board.ports[6].player=currPlayer.getTurn();
            currPlayer.portsOwned.push_back(6);
        }
        else if ((vertNum==38)||(vertNum==28)){
            board.ports[7].player=currPlayer.getTurn();
            currPlayer.portsOwned.push_back(7);
        }
        else if ((vertNum==17)||(vertNum==7)){
            board.ports[8].player=currPlayer.getTurn();
            currPlayer.portsOwned.push_back(8);
        }
        cout << "settlement placed\n\n";
        currPlayer.victoryPoints++;
    }
return;
}

void Catan::placeFirstSettlement(Player& currPlayer, int &vertNum){
    if (board.validSettle(currPlayer.getTurn(), vertNum)==1){
        cout << "\nvertex is occupied, please choose another location\n";
        cin >> vertNum;
        placeFirstSettlement(currPlayer, vertNum);
        return;
    }
    else if (board.validSettle(currPlayer.getTurn(), vertNum)==2){
        cout << "\nthere is already a building nearby, please choose another location\n";
        cin >> vertNum;
        placeFirstSettlement(currPlayer, vertNum);
        return;
    }
    else {
        board.setSettle(currPlayer.getTurn(), vertNum);
        if ((vertNum==0)||(vertNum==1)){
            board.ports[0].player=currPlayer.getTurn();
            currPlayer.portsOwned.push_back(0);
        }
        else if ((vertNum==3)||(vertNum==4)){
            board.ports[1].player=currPlayer.getTurn();
            currPlayer.portsOwned.push_back(1);
        }
        else if ((vertNum==14)||(vertNum==15)){
            board.ports[2].player=currPlayer.getTurn();
            currPlayer.portsOwned.push_back(2);
        }
        else if ((vertNum==26)||(vertNum==37)){
            board.ports[3].player=currPlayer.getTurn();
            currPlayer.portsOwned.push_back(3);
        }
        else if ((vertNum==46)||(vertNum==45)){
            board.ports[4].player=currPlayer.getTurn();
            currPlayer.portsOwned.push_back(4);
        }
        else if ((vertNum==51)||(vertNum==50)){
            board.ports[5].player=currPlayer.getTurn();
            currPlayer.portsOwned.push_back(5);
        }
        else if ((vertNum==48)||(vertNum==47)){
            board.ports[6].player=currPlayer.getTurn();
            currPlayer.portsOwned.push_back(6);
        }
        else if ((vertNum==38)||(vertNum==28)){
            board.ports[7].player=currPlayer.getTurn();
            currPlayer.portsOwned.push_back(7);
        }
        else if ((vertNum==17)||(vertNum==7)){
            board.ports[8].player=currPlayer.getTurn();
            currPlayer.portsOwned.push_back(8);
        }
        cout<<"settlement placed\n\n";
        (currPlayer.victoryPoints)++;
        return;
    }
}

void Catan::placeRoad(Player currPlayer, int edgeNum){
    if(board.validRoad(currPlayer.getTurn(), edgeNum)==1){
        cout << "\nedge is occupied, please choose another location\n";
        cin >> edgeNum;
        placeRoad(currPlayer, edgeNum);
        return;
    }

    if(board.validRoad(currPlayer.getTurn(), edgeNum)==3){
        cout << "\nyou must build next to an existing road or settlement, please choose another location\n";
        cin >> edgeNum;
        placeRoad(currPlayer, edgeNum);
        return;
    }

    else {
        board.setRoad(currPlayer.getTurn(), edgeNum);
        currPlayer.numRoads++;
        cout<<"road placed\n\n";
        return;
    }
}

void Catan::placeCity(Player& currPlayer, int vertNum){
    if (board.vertLayer[vertNum].occupiedBy!= currPlayer.getTurn()){
        cout << "\nYour settlement is not at this location.\nPlease select another location.\n";
        cin >> vertNum;
        placeCity(currPlayer, vertNum);
    }

    else{
        board.setCity(currPlayer.getTurn(), vertNum);
        cout << "city placed\n";
        currPlayer.victoryPoints++;
    }
}

void Catan::setLongestRoad() {

}

void Catan::setLargestArmy(){
    //if no one has a soldier card played, return
    int currGreatest = 0;
    playerNum greatestPlayer = NOONE;
    for (vector<Player>::iterator it = turnplayerList.begin(); it != turnplayerList.end(); it++) {
        if((*it).DevPlayed.soldierCard>currGreatest){
            currGreatest = (*it).DevPlayed.soldierCard;
            //remove honor and victory points from current greatestPlayer
            if(greatestPlayer!=NOONE){
                turnplayerList[greatestPlayer].hasLargestArmy = false;
                turnplayerList[greatestPlayer].victoryPoints--;
            }
            //give honor and set new greatestPlayer
            greatestPlayer=(*it).getTurn();
            (*it).hasLargestArmy = true;
            (*it).victoryPoints++;
        }
    }
}

void Catan::trade(){
    int cardCount=0;
    bool inTrade=true;
    bool invalid =false;
    string tradeTo;
    string recIn;
    string answer;
    string choiceIn;
    resourceType typeOut;
    int numIn;
    while(inTrade==true){
        inTrade=false;
        cout << turnplayerList[currentPlayer].getName() << ", you have:\n";
        if ((turnplayerList[currentPlayer].ResourceHand.stone)>0){
            cout << "\tStone:\t" << turnplayerList[currentPlayer].ResourceHand.stone << endl;
            cardCount++;
        }
        if (turnplayerList[currentPlayer].ResourceHand.grain>0){
            cout << "\tGrain:\t" << turnplayerList[currentPlayer].ResourceHand.grain<< endl;
            cardCount++;
        }
        if (turnplayerList[currentPlayer].ResourceHand.lumber>0){
            cout << "\tLumber:\t" << turnplayerList[currentPlayer].ResourceHand.lumber<< endl;
            cardCount++;
        }
        if (turnplayerList[currentPlayer].ResourceHand.wool>0){
            cout << "\tWool:\t" << turnplayerList[currentPlayer].ResourceHand.wool<< endl;
            cardCount++;
        }
        if (turnplayerList[currentPlayer].ResourceHand.brick>0){
            cout << "\tBrick:\t" << turnplayerList[currentPlayer].ResourceHand.brick<< endl;
            cardCount++;
        }
        if (cardCount==0){
            cout << "You have no cards to trade.\n";
            inTrade=false;
            delay(2);
            continue;
        }
        cout << "What would you like to put up for trade?\n";
        string recChoice;
        cin >> recChoice;
        string choiceOut;
        int numChoiceOut;
        do{ //checks input for validity
            invalid=false;
            cout << "in do-while\n";
            if ((recChoice.compare("Stone")==0)){
                cout << "Choose the amount of Stone you want to give (1-" << turnplayerList[currentPlayer].ResourceHand.stone <<
                        "), or enter Back:\n";
                cin >> choiceOut;
                //
                //replace following with
                //checkInt function!!!!!
                //
                revalidInputStone:
                if (isdigit(choiceOut[0])==0){
                    cout << "seeing if choiceOut is back\n";
                    if (choiceOut.compare("Back")==0){
                        inTrade=false;
                        cout << "Closing trade negotiations.\n";
                        delay(2);
                        goto endTrade;
                    }
                }
                //checking to make sure numchoice is an int, if not re-prompts for entry and re-checks
                cout << "choice out is not back\n";
                for (int i=0;i<(int)choiceOut.size();i++){
                    if (isdigit(choiceOut[i])==0){
                        cout << "Invalid selection. Please re-enter amount of Stone you are giving. Or enter 'Back'\n";
                        cin >> choiceOut;
                        goto revalidInputStone;
                    }
                }
                numChoiceOut=atoi(choiceOut.c_str());
            }
            //cout << "Not Stone\n";
            else if ((recChoice.compare("Grain")==0)){
                cout << "Choose the amount of Grain you want to give (1-" << turnplayerList[currentPlayer].ResourceHand.grain <<
                        "), or enter Back:\n";
                cin >> choiceOut;
                //
                //replace following with
                //checkInt function!!!!!
                //
                revalidInputGrain:
                if (isdigit(choiceOut[0])==0){
                    if (choiceOut.compare("Back")==0){
                        inTrade=false;
                        continue;
                    }
                }
                //checking to make sure numchoice is an int, if not re-prompts for entry and re-checks
                for (int i=0;i<(int)choiceOut.size();i++){
                    if (isdigit(choiceOut[i])==0){
                        cout << "Invalid selection. Please re-enter amount of Grain you are giving. Or enter 'Back'\n";
                        cin >> choiceOut;
                        goto revalidInputGrain;
                    }
                }
                numChoiceOut=atoi(choiceOut.c_str());
            }
            //cout << "Not Grain\n";
            else if ((recChoice.compare("Lumber")==0)){
                cout << "Choose the amount of Lumber you want to give (1-" << turnplayerList[currentPlayer].ResourceHand.lumber <<
                        "), or enter Back:\n";
                cin >> choiceOut;
                //
                //replace following with
                //checkInt function!!!!!
                //
                revalidInputLumber:
                if (isdigit(choiceOut[0])==0){
                    if (choiceOut.compare("Back")==0){
                        inTrade=false;
                        cout << "Closing trade negotiations.\n";
                        delay(2);
                        goto endTrade;
                    }
                }
                //checking to make sure numchoice is an int, if not re-prompts for entry and re-checks
                for (int i=0;i<(int)choiceOut.size();i++){
                    if (isdigit(choiceOut[i])==0){
                        cout << "Invalid selection. Please re-enter amount of Lumber you are giving. Or enter 'Back'\n";
                        cin >> choiceOut;
                        goto revalidInputLumber;
                    }
                }
                numChoiceOut=atoi(choiceOut.c_str());
            }
            //cout << "Not Lumber\n";
            else if ((recChoice.compare("Wool")==0)){
                cout << "Choose the amount of Wool you want to give (1-" << turnplayerList[currentPlayer].ResourceHand.wool <<
                        "), or enter Back:\n";
                cin >> choiceOut;
                //
                //replace following with
                //checkInt function!!!!!
                //
                revalidInputWool:
                if (isdigit(choiceOut[0])==0){
                    if (choiceOut.compare("Back")==0){
                        inTrade=false;
                        cout << "Closing trade negotiations.\n";
                        delay(2);
                        goto endTrade;
                    }
                }
                //checking to make sure numchoice is an int, if not re-prompts for entry and re-checks
                for (int i=0;i<(int)choiceOut.size();i++){
                    if (isdigit(choiceOut[i])==0){
                        cout << "Invalid selection. Please re-enter amount of Wool you are giving. Or enter 'Back'\n";
                        cin >> choiceOut;
                        goto revalidInputWool;
                    }
                }
                numChoiceOut=atoi(choiceOut.c_str());
            }
            //cout << "Not Wool\n";
            else if ((recChoice.compare("Brick")==0)){
                cout << "Choose the amount of Brick you want to give (1-" << turnplayerList[currentPlayer].ResourceHand.brick <<
                        "), or enter Back:\n";
                cin >> choiceOut;
                //
                //replace following with
                //checkInt function!!!!!
                //
                revalidInputBrick:
                if (isdigit(choiceOut[0])==0){
                    if (choiceOut.compare("Back")==0){
                        inTrade=false;
                        cout << "Closing trade negotiations.\n";
                        delay(2);
                        goto endTrade;
                    }
                }
                //checking to make sure numchoice is an int, if not re-prompts for entry and re-checks
                for (int i=0;i<(int)choiceOut.size();i++){
                    if (isdigit(choiceOut[i])==0){
                        cout << "Invalid selection. Please re-enter amount of Brick you are giving. Or enter 'Back'\n";
                        cin >> choiceOut;
                        goto revalidInputBrick;
                    }
                }
                numChoiceOut=atoi(choiceOut.c_str());
            }
            //cout << "Not Brick\n";
            else if (recChoice.compare("Back")==0){
                cout << "Closing trade negotiations.\n";
                delay(2);
                goto endTrade;
            }
            else{
                cout << "Invalid selection. Please re-enter type of resource you are giving. Or enter 'Back'\n";
                cin >> recChoice;
                invalid=true;
            }

        }while(invalid==true);
            do{ //again, checking for validity
                invalid=false;
                cout << "Please enter the resource you want for your " << recChoice << ". (Stone Grain Lumber Wool or Brick):\n";
                cin >> recIn;
                if ((recIn.compare("Stone")==1) && (recIn.compare("Grain")==1) && (recIn.compare("Lumber")==1)
                    && (recIn.compare("Wool")==1) && (recIn.compare("Brick")==1) && (recIn.compare("Back")==1)){
                    cout << "Invalid selection. Please re-enter.\n";
                    cin >> recIn;
                    invalid=true;
                }
            }while(invalid==true);
            if (recIn.compare("Back")==0){
                cout << "Closing trade negotiations.\n";
                delay(2);
                goto endTrade;
            }



            cout << "Please enter how many " << recIn << " resources you would like.\n";
            cin >> choiceIn;
            //
            //replace following with
            //checkInt function!!!!!
            //
            revalidInputTradeNum:
            if (isdigit(choiceIn[0])==0){
                if (choiceIn.compare("Back")==0){
                    inTrade=false;
                    cout << "Closing trade negotiations.\n";
                    delay(2);
                    goto endTrade;
                }
            }
            //checking to make sure numchoice is an int, if not re-prompts for entry and re-checks
            for (int i=0;i<(int)choiceIn.size();i++){
                if (isdigit(choiceIn[i])==0){
                    cout << "Invalid selection. Please re-enter amount of Brick you are giving. Or enter 'Back'\n";
                    cin >> choiceIn;
                    goto revalidInputTradeNum;
                }
            }
            numIn=atoi(choiceIn.c_str());
            cout << "Who would like to accept this trade?\n\tResource from " << turnplayerList[currentPlayer].getName()
                    << ":\tNumber of resources\n\t" << recChoice << "\t" << numChoiceOut << endl;
            cout << "\tResource you give:\t Number of resources:\n\t" << recIn << "\t" << numIn << endl;

            cout << "Please enter your name to accept. If no one accepts, enter NOBODY.\n";
            cin >> tradeTo;
            int numTo;
            stillInval:
            do{ //check if input is ok
                invalid=false;
                for (int i=0;i<(int)turnplayerList.size();i++){
                    if ((tradeTo.compare(turnplayerList[i].getName())==0) || tradeTo.compare("NOBODY")==0){
                        break;
                    }
                    else if(i==((int)(turnplayerList.size())-1)){
                        cout << "Invalid entry. Please re-enter name.\n";
                        cin >> tradeTo;
                        goto stillInval;
                    }
                }
                if (tradeTo.compare("NOBODY")==0){
                    cout << "Nobody accepted the trade. Closing negotiations.\n";
                    delay(2);
                    goto endTrade;
                }

                for (int i=0;;i++){
                    if (tradeTo.compare(turnplayerList[i].getName())==0){
                        numTo=i;
                        break;
                    }
                }

                if (recChoice.compare("Stone")==0)
                    typeOut = STONE;
                if (recChoice.compare("Lumber")==0)
                    typeOut = LUMBER;
                if (recChoice.compare("Grain")==0)
                    typeOut = GRAIN;
                if (recChoice.compare("Wool")==0)
                    typeOut = WOOL;
                if (recChoice.compare("Brick")==0)
                    typeOut = BRICK;



                if (recIn.compare("Stone")==0){ //trading stone
                    if (turnplayerList[numTo].ResourceHand.stone < numIn){
                        cout << "You do not have enough Stone. Please enter another player, or enter NOBODY\n";
                        invalid=true;
                        cin >> tradeTo;
                        continue;
                    }
                    for (int i=0;i<numIn;i++){
                        turnplayerList[currentPlayer].recIn(STONE);
                        turnplayerList[numTo].recOut(STONE);
                    }
                    for (int i=0;i<numChoiceOut;i++){
                        turnplayerList[currentPlayer].recOut(typeOut);
                        turnplayerList[numTo].recIn(typeOut);
                    }

                    cout << "You have successfully traded " << numChoiceOut << " " << recChoice << " for "
                            << numIn << " " << recIn << ". Congratz.\n";
                    cout << "would you like to make another trade? (Yes or No)\n";
                    string tradeAgain;
                    cin >> tradeAgain;
                    if (tradeAgain.compare("Yes")==0){
                        inTrade=true;
                        continue;
                    }
                }

                if (recIn.compare("Lumber")==0){ //trading Lumber
                    if (turnplayerList[numTo].ResourceHand.lumber < numIn){
                        cout << "You do not have enough Lumber. Please enter another player, or enter NOBODY\n";
                        invalid=true;
                        cin >> tradeTo;
                        continue;
                    }
                    for (int i=0;i<numIn;i++){
                        turnplayerList[currentPlayer].recIn(LUMBER);
                        turnplayerList[numTo].recOut(LUMBER);
                    }
                    for (int i=0;i<numChoiceOut;i++){
                        turnplayerList[currentPlayer].recOut(typeOut);
                        turnplayerList[numTo].recIn(typeOut);
                    }

                    cout << "You have successfully traded " << numChoiceOut << " " << recChoice << " for "
                            << numIn << " " << recIn << ". Congratz.\n";
                    cout << "would you like to make another trade? (Yes or No)\n";
                    string tradeAgain;
                    cin >> tradeAgain;
                    if (tradeAgain.compare("Yes")==0){
                        inTrade=true;
                        continue;
                    }
                }

                if (recIn.compare("Grain")==0){
                    if (turnplayerList[numTo].ResourceHand.grain < numIn){
                        cout << "You do not have enough Grain. Please enter another player, or enter NOBODY\n";
                        invalid=true;
                        cin >> tradeTo;
                        continue;
                    }
                    for (int i=0;i<numIn;i++){
                        turnplayerList[currentPlayer].recIn(GRAIN);
                        turnplayerList[numTo].recOut(GRAIN);
                    }
                    for (int i=0;i<numChoiceOut;i++){
                        turnplayerList[currentPlayer].recOut(typeOut);
                        turnplayerList[numTo].recIn(typeOut);
                    }

                    cout << "You have successfully traded " << numChoiceOut << " " << recChoice << " for "
                            << numIn << " " << recIn << ". Congratz.\n";
                    cout << "would you like to make another trade? (Yes or No)\n";
                    string tradeAgain;
                    cin >> tradeAgain;
                    if (tradeAgain.compare("Yes")==0){
                        inTrade=true;
                        continue;
                    }
                }

                if (recIn.compare("Wool")==0){
                    if (turnplayerList[numTo].ResourceHand.wool < numIn){
                        cout << "You do not have enough Wool. Please enter another player, or enter NOBODY\n";
                        invalid=true;
                        cin >> tradeTo;
                        continue;
                    }
                    for (int i=0;i<numIn;i++){
                        turnplayerList[currentPlayer].recIn(WOOL);
                        turnplayerList[numTo].recOut(WOOL);
                    }
                    for (int i=0;i<numChoiceOut;i++){
                        turnplayerList[currentPlayer].recOut(typeOut);
                        turnplayerList[numTo].recIn(typeOut);
                    }

                    cout << "You have successfully traded " << numChoiceOut << " " << recChoice << " for "
                            << numIn << " " << recIn << ". Congratz.\n";
                    cout << "would you like to make another trade? (Yes or No)\n";
                    string tradeAgain;
                    cin >> tradeAgain;
                    if (tradeAgain.compare("Yes")==0){
                        inTrade=true;
                        continue;
                    }
                }

                if (recIn.compare("Brick")==0){
                    if (turnplayerList[numTo].ResourceHand.brick < numIn){
                        cout << "You do not have enough Brick. Please enter another player, or enter NOBODY\n";
                        invalid=true;
                        cin >> tradeTo;
                        continue;
                    }
                    for (int i=0;i<numIn;i++){
                        turnplayerList[currentPlayer].recIn(BRICK);
                        turnplayerList[numTo].recOut(BRICK);
                    }
                    for (int i=0;i<numChoiceOut;i++){
                        turnplayerList[currentPlayer].recOut(typeOut);
                        turnplayerList[numTo].recIn(typeOut);
                    }

                    cout << "You have successfully traded " << numChoiceOut << " " << recChoice << " for "
                            << numIn << " " << recIn << ". Congratz.\n";
                    cout << "would you like to make another trade? (Yes or No)\n";
                    string tradeAgain;
                    cin >> tradeAgain;
                    if (tradeAgain.compare("Yes")==0){
                        inTrade=true;
                        continue;
                    }
                }
            }while (invalid==true);

            endTrade:
            cout << "Trade negotiations concluded.\n";
    }
}

void Catan::portTrade(){
    string recOut;
    string recIn;
    int numOut=2;
    bool invalid;
    if (turnplayerList[currentPlayer].portsOwned.empty()){
        cout << "Since you dont own any ports, you can only trade 4:1.\n";
        trade4_1();
        return;
    }
    string choice;
    cout << "Would you like to trade 4:1 or trade with a port you own? (enter 4:1 or Port)\n\t";
    do{
        invalid=false;
        cin >> choice;
        if (!(choice.compare("4:1")==0)&&!(choice.compare("Port")==0)&&!(choice.compare("Back")==0)){
            cout << "Invalid selection. Please Re-enter.\n\t";
            cin >>choice;
            invalid=true;
        }
    }while (invalid==true);
    if (choice.compare("4:1")==0){
        trade4_1();
        return;
    }
    else if (choice.compare("Back")==0){
        cout << "Closing trade negotiations.\n";
        delay(2);
        return;
    }
    else if (choice.compare("Port")==0){
        cout << "You may choose from the following Ports:\n";
        for (unsigned int i=0;i<(turnplayerList[currentPlayer].portsOwned.size()-1);i++){
            if (board.ports[turnplayerList[currentPlayer].portsOwned[i]].type==0)
                cout << "2 Stone for any 1 resource\n";
            if (board.ports[turnplayerList[currentPlayer].portsOwned[i]].type==1)
                cout << "2 Grain for any 1 resource\n";
            if (board.ports[turnplayerList[currentPlayer].portsOwned[i]].type==2)
                cout << "2 Lumber for any  resource\n";
            if (board.ports[turnplayerList[currentPlayer].portsOwned[i]].type==3)
                cout << "2 Wool for any 1 resource\n";
            if (board.ports[turnplayerList[currentPlayer].portsOwned[i]].type==4)
                cout << "2 Brick for any 1 resource\n";
            if (board.ports[turnplayerList[currentPlayer].portsOwned[i]].type==5)
                cout << "3 of any resource for any 1 resource\n";
        }
        cout << "To choose a port, enter the name of the resource, 3:1, or Back.\n\t";
        cin >> recOut;
        do{
            invalid=false;
            if(!(recOut.compare("Back")==0)&&!(recOut.compare("Stone")==0)&&!(recOut.compare("Grain")==0)&&!(recOut.compare("Lumber")==0)&&
                !(recOut.compare("Wool")==0)&&!(recOut.compare("Brick")==0)&&!(recOut.compare("3:1")==0)){
                cout << "Invalid selection. Please re-enter.\n\t";
                cin >> recOut;
                invalid=true;
            }
        }while(invalid==true);
        if (recOut.compare("Back")==0){
           cout << "Closing trade negotiations.\n";
           delay(2);
           return;
        }
        int port;
        do{
            if (recOut.compare("Back")==0){
               cout << "Closing trade negotiations.\n";
               delay(2);
               return;
            }
            invalid=false;
            if (recOut.compare("Stone")==0){
                port=0;
            }
            else if (recOut.compare("Grain")==0){
                port=1;
            }
            else if (recOut.compare("Lumber")==0){
                port=2;
            }
            else if (recOut.compare("Wool")==0){
                port=3;
            }
            else if (recOut.compare("Brick")==0){
                port=4;
            }
            else if (recOut.compare("3:1")==0){
                port=5;
            }
            for (unsigned int i=0;i<turnplayerList[currentPlayer].portsOwned.size();i++){
                if (board.ports[turnplayerList[currentPlayer].portsOwned[i]].type==port)
                    break;
                if (i==(turnplayerList[currentPlayer].portsOwned.size()-1)){
                    cout << "You do not own this port. Please select another port, or enter Back.\n";
                    cin >> recOut;
                    invalid=true;
                }
            }
            if (port==5){
                cout << "Please select the resource you want to give up 3 of.\n\t";
                cin >> recOut;
                do{
                    invalid=false;
                    if(!(recOut.compare("Back")==0)&&!(recOut.compare("Stone")==0)&&!(recOut.compare("Grain")==0)&&!(recOut.compare("Lumber")==0)&&
                        !(recOut.compare("Wool")==0)&&!(recOut.compare("Brick")==0)){
                        cout << "Invalid selection. Please re-enter.\n\t";
                        cin >> recOut;
                        invalid=true;
                    }
                }while(invalid==true);
                if (recOut.compare("Back")==0){
                   cout << "Closing trade negotiations.\n";
                   delay(2);
                   return;
                }
                numOut=3;
            }
        }while(invalid==true);
        cout << "Now enter the resource you would like to receive.\n\t";
        cin >> recIn;
        do{
            invalid=false;
            if(!(recIn.compare("Back")==0)&&!(recIn.compare("Stone")==0)&&!(recIn.compare("Grain")==0)&&!(recIn.compare("Lumber")==0)&&
                !(recIn.compare("Wool")==0)&&!(recIn.compare("Brick")==0)){
                cout << "Invalid selection. Please re-enter.\n\t";
                cin >> recIn;
                invalid=true;
            }
        }while(invalid==true);
        if (recIn.compare("Back")==0){
           cout << "Closing trade negotiations.\n";
           delay(2);
           return;
        }
        if (recOut.compare("Stone")==0){
            turnplayerList[currentPlayer].ResourceHand.stone-=numOut;
        }
        else if (recOut.compare("Grain")==0){
            turnplayerList[currentPlayer].ResourceHand.stone-=numOut;
        }
        else if (recOut.compare("Lumber")==0){
            turnplayerList[currentPlayer].ResourceHand.stone-=numOut;
        }
        else if (recOut.compare("Wool")==0){
            turnplayerList[currentPlayer].ResourceHand.stone-=numOut;
        }
        else if (recOut.compare("Brick")==0){
            turnplayerList[currentPlayer].ResourceHand.stone-=numOut;
        }

        if (recIn.compare("Stone")==0){
            turnplayerList[currentPlayer].ResourceHand.stone+=1;
        }
        else if (recIn.compare("Grain")==0){
            turnplayerList[currentPlayer].ResourceHand.grain+=1;
        }
        else if (recIn.compare("Lumber")==0){
            turnplayerList[currentPlayer].ResourceHand.lumber+=1;
        }
        else if (recIn.compare("Wool")==0){
            turnplayerList[currentPlayer].ResourceHand.wool+=1;
        }
        else if (recIn.compare("Brick")==0){
            turnplayerList[currentPlayer].ResourceHand.brick+=1;
        }
    }
    cout << "Congrats. You successfully trade " << numOut << " " << recOut << " for 1 " << recIn << ".\n";
}

void Catan::trade4_1(){
    string recIn;
    string recOut;
    bool invalid;
    cout << "Enter a resource to give or enter Back\n\t";
    cin >> recOut;
    do{ //sanitize input with giant if statement
        invalid=false;
        if(!(recOut.compare("Back")==0)&&!(recOut.compare("Stone")==0)&&!(recOut.compare("Grain")==0)&&!(recOut.compare("Lumber")==0)&&
            !(recOut.compare("Wool")==0)&&!(recOut.compare("Brick")==0)){
            cout << "Invalid selection. Please re-enter.\n\t";
            cin >> recOut;
            invalid=true;
        }
    }while(invalid==true);
    if (recOut.compare("Back")==0){
        cout << "Closing trade negotiations.\n";
        delay(2);
        return;
    }
    cout << "Now enter the resource you want to trade for, or enter Back.\n\t";
    cin >> recIn;
    do{ //sanitize input with giant if statement
        invalid=false;
        if(!(recIn.compare("Back")==0)&&!(recIn.compare("Stone")==0)&&!(recIn.compare("Grain")==0)&&!(recIn.compare("Lumber")==0)&&
            !(recIn.compare("Wool")==0)&&!(recIn.compare("Brick")==0)){
            cout << "Invalid selection. Please re-enter.\n\t";
            cin >> recIn;
            invalid=true;
        }
    }while(invalid==true);
    if (recIn.compare("Back")==0){
        cout << "Closing trade negotiations.\n";
        delay(2);
        return;
    }
    if (recOut.compare("Stone")==0){
        turnplayerList[currentPlayer].ResourceHand.stone=turnplayerList[currentPlayer].ResourceHand.stone-4;
    }
    else if (recOut.compare("Grain")==0){
        turnplayerList[currentPlayer].ResourceHand.grain=turnplayerList[currentPlayer].ResourceHand.grain-4;
    }
    else if (recOut.compare("Lumber")==0){
        turnplayerList[currentPlayer].ResourceHand.lumber=turnplayerList[currentPlayer].ResourceHand.lumber-4;
    }
    else if (recOut.compare("Wool")==0){
        turnplayerList[currentPlayer].ResourceHand.wool=turnplayerList[currentPlayer].ResourceHand.wool-4;
    }
    else if (recOut.compare("Brick")==0){
        turnplayerList[currentPlayer].ResourceHand.brick=turnplayerList[currentPlayer].ResourceHand.brick-4;
    }
    if (recIn.compare("Stone")==0){
        turnplayerList[currentPlayer].ResourceHand.stone++;
    }
    else if (recIn.compare("Grain")==0){
        turnplayerList[currentPlayer].ResourceHand.grain++;
    }
    else if (recIn.compare("Lumber")==0){
        turnplayerList[currentPlayer].ResourceHand.lumber++;
    }
    else if (recIn.compare("Wool")==0){
        turnplayerList[currentPlayer].ResourceHand.wool++;
    }
    else if (recIn.compare("Brick")==0){
        turnplayerList[currentPlayer].ResourceHand.brick++;
    }
    cout << "Successfully traded 4 " << recOut << " for 1 " << recIn << ".\n";
}

int Catan::diceRoll(Player currPlayer){
    string input="";
    while (input!="roll"){
       cout << "\n\n" << currPlayer.getName() << ", type 'roll' to roll the die" << endl;
       cin >> input;
    }
    int dieNum;
    timeval Time;
    gettimeofday(&Time, NULL);
    long timeseed=Time.tv_usec ;
//    cout << "time at roll is" << timeseed << endl;
    srand(timeseed);
    int randNum = rand();
//    cout << "random number is " << randNum << endl;
    dieNum = 1 + randNum%6; // rolls die, number between 1 and 6;
    cout << "You rolled a " << dieNum << endl;
    return dieNum;
}

void Catan::yield(int rollNum){

    for (vector<Player>::iterator k =turnplayerList.begin(); k!=turnplayerList.end(); k++){
        if ((*k).victoryPoints==7){

        }
    }

    if (rollNum<7){
        if (rollNum==2){ //yield resources for only number location
            for (int i=0;i<6;i++){
                if (board.vertLayer[board.hexLayer[board.yieldNums[0].hex1].assVert[i]].occupiedBy!=NOONE){
                    turnplayerList[board.vertLayer[board.hexLayer[board.yieldNums[0].hex1].assVert[i]].occupiedBy].addRec(board.hexLayer[board.yieldNums[0].hex1].terrType);
                    if (board.vertLayer[board.hexLayer[board.yieldNums[0].hex1].assVert[i]].occByType==2){
                        turnplayerList[board.vertLayer[board.hexLayer[board.yieldNums[0].hex1].assVert[i]].occupiedBy].addRec(board.hexLayer[board.yieldNums[0].hex1].terrType);
                    }
                }
            }
        }
        else {
            for (int i=0;i<6;i++){ //yield resources for first location
                 if (board.vertLayer[board.hexLayer[board.yieldNums[rollNum-2].hex1].assVert[i]].occupiedBy!=NOONE){
                     turnplayerList[board.vertLayer[board.hexLayer[board.yieldNums[rollNum-2].hex1].assVert[i]].occupiedBy].addRec(board.hexLayer[board.yieldNums[rollNum-2].hex1].terrType);
                     if (board.vertLayer[board.hexLayer[board.yieldNums[rollNum-2].hex1].assVert[i]].occByType==2)
                         turnplayerList[board.vertLayer[board.hexLayer[board.yieldNums[rollNum-2].hex1].assVert[i]].occupiedBy].addRec(board.hexLayer[board.yieldNums[rollNum-2].hex1].terrType);
                 }
            }
            for (int i=0;i<6;i++){ //yield resources for second location
                if (board.vertLayer[board.hexLayer[board.yieldNums[rollNum-2].hex2].assVert[i]].occupiedBy!=NOONE){
                    turnplayerList[board.vertLayer[board.hexLayer[board.yieldNums[rollNum-2].hex2].assVert[i]].occupiedBy].addRec(board.hexLayer[board.yieldNums[rollNum-2].hex2].terrType);
                    if (board.vertLayer[board.hexLayer[board.yieldNums[rollNum-2].hex2].assVert[i]].occByType==2)
                        turnplayerList[board.vertLayer[board.hexLayer[board.yieldNums[rollNum-2].hex2].assVert[i]].occupiedBy].addRec(board.hexLayer[board.yieldNums[rollNum-2].hex2].terrType);
                }
            }
        }
    }
    else {
        if (rollNum==12){ //yield resources for only number location
            for (int i=0;i<6;i++){
                if (board.vertLayer[board.hexLayer[board.yieldNums[9].hex1].assVert[i]].occupiedBy!=NOONE){
                    turnplayerList[board.vertLayer[board.hexLayer[board.yieldNums[9].hex1].assVert[i]].occupiedBy].addRec(board.hexLayer[board.yieldNums[9].hex1].terrType);
                    if (board.vertLayer[board.hexLayer[board.yieldNums[9].hex1].assVert[i]].occByType==2)
                        turnplayerList[board.vertLayer[board.hexLayer[board.yieldNums[9].hex1].assVert[i]].occupiedBy].addRec(board.hexLayer[board.yieldNums[9].hex1].terrType);
                }
            }
        }
        else {
            for (int i=0;i<6;i++){ //yield resources for first location
                 if (board.vertLayer[board.hexLayer[board.yieldNums[rollNum-3].hex1].assVert[i]].occupiedBy!=NOONE){
                     turnplayerList[board.vertLayer[board.hexLayer[board.yieldNums[rollNum-3].hex1].assVert[i]].occupiedBy].addRec(board.hexLayer[board.yieldNums[rollNum-3].hex1].terrType);
                     if (board.vertLayer[board.hexLayer[board.yieldNums[rollNum-3].hex1].assVert[i]].occByType==2)
                         turnplayerList[board.vertLayer[board.hexLayer[board.yieldNums[rollNum-3].hex1].assVert[i]].occupiedBy].addRec(board.hexLayer[board.yieldNums[rollNum-3].hex1].terrType);
                 }
            }
            for (int i=0;i<6;i++){ //yield resources for second location
                if (board.vertLayer[board.hexLayer[board.yieldNums[rollNum-3].hex2].assVert[i]].occupiedBy!=NOONE){
                    turnplayerList[board.vertLayer[board.hexLayer[board.yieldNums[rollNum-3].hex2].assVert[i]].occupiedBy].addRec(board.hexLayer[board.yieldNums[rollNum-3].hex2].terrType);
                    if (board.vertLayer[board.hexLayer[board.yieldNums[rollNum-3].hex2].assVert[i]].occByType==2)
                        turnplayerList[board.vertLayer[board.hexLayer[board.yieldNums[rollNum-3].hex2].assVert[i]].occupiedBy].addRec(board.hexLayer[board.yieldNums[rollNum-3].hex2].terrType);
                }
            }
        }
    }
}

Player* Catan::goesFirst(vector<Player> playerList)
{
    int maxRoll=0;
    int currRoll;
    vector<Player> isFirst;
    for (unsigned int i=0;i<playerList.size();i++){
        currRoll=diceRoll(playerList.at(i));
        if(currRoll==maxRoll){
            isFirst.push_back(playerList.at(i));
        }
        else if (currRoll>maxRoll){
            isFirst.clear();
            isFirst.push_back(playerList.at(i));
            maxRoll=currRoll;
        }
    }
    if (isFirst.size()!=1){
        vector<Player> temp = isFirst;
        isFirst.clear();
        cout << "Players ";
        for (int i=0;i<(int)temp.size();i++)
            cout << temp[i].getName() << " and ";
        cout << "tied for first. Rerolling for these players.\n";
        isFirst.push_back(*goesFirst(temp));
        return &isFirst[0];
    }
//    cout << "Player " << isFirst[0].getName() << " is first.\n";
    return &isFirst[0];
}

void Catan::decideOrder() {
    cout << "\nDeciding order.\n";
    Player first=*goesFirst(myplayerList);
    for (int i=0;i<(int)myplayerList.size();i++)
        cout << myplayerList[i].getName() << " is " << myplayerList[i].getTurn() << endl;
    int firstLoc=0;
//    cout << "there are " << myplayerList.size() << "players\n";
//    cout << "finding firstLoc\n" << endl;
    while (myplayerList[firstLoc].getName()!=first.getName()){
//      cout << "player " << myplayerList[firstLoc].getName() << " is not first.\n";
        firstLoc++;
    }
//  cout << "found first loc at " << firstLoc << endl;
    int i=firstLoc;
    int turnCount=0;
    while(i<(int)myplayerList.size()){
        turnplayerList.push_back(myplayerList[i]);
        turnplayerList[turnCount].setTurn(intToNum(turnCount));
   //     cout << "player " << myplayerList[i].getName() << " is " << i << endl;
        i++;
        turnCount++;
    }
//    cout << "back to beginning\n";
    i=0;
    while(i<firstLoc){
        turnplayerList.push_back((myplayerList[i]));
        turnplayerList[turnCount].setTurn(intToNum(turnCount));
    //    cout << "player " << myplayerList[i].getName() << " is " << i << endl;
    i++;
    turnCount++;
    }
}

void Catan::endTurn(){
    currentPlayer=(currentPlayer+1)%turnplayerList.size();
}

void Catan::buildSettle(){
    cout << "Please select a tile to build at:\n";
    for (int i=0; i<19; i++){
        bool avail=true;
        for (int j=0;j<6;j++){
            if (board.validSettle((playerNum)currentPlayer,board.hexLayer[i].assVert[j])==0)
                break;
            else if (i==5)
                avail=false;
        }
        if (avail==true)
            cout << "\t" << i;
    }
    cout<<endl;
    int hexChoice;
    cin >> hexChoice;
    cout << "Select a vertex to build at:\t";
    for (int i=0;i<6;i++){
        if (board.validSettle((playerNum) currentPlayer,board.hexLayer[hexChoice].assVert[i])==0){
            if (i==0)
                cout << "UL\t";
            else if (i==1)
                cout << "Tp\t";
            else if (i==2)
                cout << "UR\t";
            else if (i==3)
                cout << "LR\t";
            else if (i==4)
                cout << "Bt\t";
            else
                cout << "LL";
        }
    }
    cout << "\n(select from the following)\t\t";
    for(int i = 0; i<6; i++){
        if (board.validSettle((playerNum) currentPlayer,board.hexLayer[hexChoice].assVert[i])==0)
            cout << board.getAssVert(hexChoice)[i] << "\t";
    }
    cout << "\n";
    int vertChoice;
    cin >> vertChoice;
    turnplayerList[currentPlayer].recOut(BRICK);
    turnplayerList[currentPlayer].recOut(GRAIN);
    turnplayerList[currentPlayer].recOut(WOOL);
    turnplayerList[currentPlayer].recOut(LUMBER);
    placeSettlement(turnplayerList[currentPlayer], vertChoice);
}

void Catan::buildRoad(){
    cout << "Please select from the following edges to place your road.\n";
    for (int i=0;i<72;i++){
        if((board.validRoad(((playerNum)currentPlayer), i)==0)||(board.validRoad(((playerNum)currentPlayer), i)==2))
            cout << "\t" << i << endl;
    }
    cout<<"  ";
    int edgeChoice;
    cin >> edgeChoice;
    turnplayerList[currentPlayer].recOut(BRICK);
    turnplayerList[currentPlayer].recOut(LUMBER);
    placeRoad(turnplayerList[currentPlayer], edgeChoice);
}

void Catan::upCity(){
    cout << "Please select a settlement to upgrade:\n";
    int count=0;
    for (int i=0;i<54;i++)
        if (board.vertLayer[i].occupiedBy==(playerNum)currentPlayer){
            cout << "\t" << i << endl;
            count++;
        }
    if (count==0){
        cout << "You have no settlements to upgrade.\n";
        return;
    }
    int settleChoice;
    cin >> settleChoice;
    turnplayerList[currentPlayer].recOut(STONE);
    turnplayerList[currentPlayer].recOut(STONE);
    turnplayerList[currentPlayer].recOut(STONE);
    turnplayerList[currentPlayer].recOut(GRAIN);
    turnplayerList[currentPlayer].recOut(GRAIN);
    placeCity(turnplayerList[currentPlayer], settleChoice);
}

playerNum Catan::intToNum(int intIn)
{
    if (intIn==0)
        return PLAYER0;
    else if (intIn==1)
        return PLAYER1;
    else if (intIn==2)
        return PLAYER2;
    else if (intIn==3)
        return PLAYER3;
    else
        return NOONE;
}

void Catan::drawfromDevDeck(){
    turnplayerList[currentPlayer].recOut(STONE);
    turnplayerList[currentPlayer].recOut(GRAIN);
    turnplayerList[currentPlayer].recOut(WOOL);

    int result = 1 + rand() % DevDeck.size;
    cout << result << endl;
    cout << "In drawfromDevDeck()\n";
    if(result <= (DevDeck.soldierCard)){
        cout << "drawing soldier" << endl;
        devIn(SOLDIER);          //I worry about passing in player this way.
        return;
    }
    else if (result <= ((DevDeck.soldierCard) + (DevDeck.victoryPointCard))){
        cout << "drawing vp" << endl;
        devIn(VICTORYPOINT);
        return;
    }
    else if (result <= ((DevDeck.soldierCard) + (DevDeck.victoryPointCard) + (DevDeck.monopolyCard))){
       cout << "drawing mono" << endl;
        devIn(MONOPOLY);
        return;
    }
    else if (result <= ((DevDeck.soldierCard) + (DevDeck.victoryPointCard) + (DevDeck.monopolyCard) + (DevDeck.roadBuildingCard))){
        cout << "drawing rb" << endl;
        devIn(ROAD_BUILDING);
        return;
    }
    else if (result <= ((DevDeck.soldierCard) + (DevDeck.victoryPointCard) + (DevDeck.monopolyCard) + (DevDeck.roadBuildingCard) + (DevDeck.yearOfPlentyCard))){
        cout << "drawing yop" << endl;
        devIn(YEAR_OF_PLENTY);
        return;
    }
    cout << "nothing happened :(\n";
}

void Catan::devIn(devType dt){
    if(dt==SOLDIER){
        turnplayerList[currentPlayer].DevHand.soldierCard++;
        DevDeck.soldierCard--;
    }
    else if(dt==VICTORYPOINT){
        turnplayerList[currentPlayer].DevHand.victoryPointCard++;
        DevDeck.victoryPointCard--;
    }
    else if(dt==MONOPOLY){
        turnplayerList[currentPlayer].DevHand.monopolyCard++;
        DevDeck.monopolyCard--;
    }
    else if(dt==ROAD_BUILDING){
        turnplayerList[currentPlayer].DevHand.roadBuildingCard++;
        DevDeck.roadBuildingCard--;
    }
    else if(dt==YEAR_OF_PLENTY){
        turnplayerList[currentPlayer].DevHand.yearOfPlentyCard++;
        DevDeck.yearOfPlentyCard--;
    }
    DevDeck.size--;
}

void Catan::devOut(devType dt){

    if(dt==SOLDIER){
        turnplayerList[currentPlayer].DevPlayed.soldierCard++;
       turnplayerList[currentPlayer].DevHand.soldierCard--;
    }
    else if(dt==VICTORYPOINT){
        turnplayerList[currentPlayer].DevPlayed.victoryPointCard++;
        turnplayerList[currentPlayer].DevHand.victoryPointCard--;
    }
    else if(dt==MONOPOLY){
        turnplayerList[currentPlayer].DevPlayed.monopolyCard++;
        turnplayerList[currentPlayer].DevHand.monopolyCard--;
    }
    else if(dt==ROAD_BUILDING){
        turnplayerList[currentPlayer].DevPlayed.roadBuildingCard++;
        turnplayerList[currentPlayer].DevHand.roadBuildingCard--;
    }
    else if(dt==YEAR_OF_PLENTY){
        turnplayerList[currentPlayer].DevPlayed.yearOfPlentyCard++;
        turnplayerList[currentPlayer].DevHand.yearOfPlentyCard--;
    }
    DevDeck.size--;
}

bool Catan::sufficientRec(string in){
    if (in.compare("Settlement")==0){
        //check to make sure that they have enough recourses in RecHand
        if ((turnplayerList[currentPlayer].ResourceHand.brick >= 1) && (turnplayerList[currentPlayer].ResourceHand.lumber >= 1) && (turnplayerList[currentPlayer].ResourceHand.grain >= 1) && (turnplayerList[currentPlayer].ResourceHand.wool) >= 1) {
            return true;
        }
    }
    else if (in.compare("Road") == 0) {
        if ((turnplayerList[currentPlayer].ResourceHand.brick >= 1) && (turnplayerList[currentPlayer].ResourceHand.lumber >= 1))
            return true;
    }

    else if (in.compare("City") == 0) {
        if ((turnplayerList[currentPlayer].ResourceHand.grain >= 2) && (turnplayerList[currentPlayer].ResourceHand.stone >= 3))
            return true;
    }

    else if (in.compare("BuyDev") == 0) {
        if ((turnplayerList[currentPlayer].ResourceHand.grain >= 1) && (turnplayerList[currentPlayer].ResourceHand.stone >= 1) && (turnplayerList[currentPlayer].ResourceHand.wool >= 1))
            return true;
    }


    return false;
}

bool Catan::checksForWinner() {
    for (vector<Player>::iterator it = turnplayerList.begin(); it != turnplayerList.end(); it++){
        if ((*it).victoryPoints == 8){
            declareWinner(*it);
            return true; // or call declare winner function
        }
    }
}

void Catan::declareWinner(Player player) {
    cout<<endl<<endl;
    cout<<"   ******************************************"<<endl;
    cout<<" //                                          \\\\"<<endl;
    cout<<"||    Congratualtions "<<player.getName();
    for(int i=0; i<= (23-((player.getName()).size())); i++){
        cout<<" ";
    }
    cout<<"||"<<endl;
    cout<<"||                                            ||"<<endl;
    cout<<"||       You've won the game!!!!!!            ||"<<endl;
    cout<<" \\\\                                          //"<<endl;
    cout<<"   ******************************************"<<endl<<endl;
}

void Catan::check7(int roll){
    if (!(roll==7))
        return;
    bool invalid;
    cout << "\t##################################\n\t##\tA 7 was rolled!!!\t##\n\t##################################\n";
    for (vector<Player>::iterator k =(turnplayerList).begin(); k!=(turnplayerList).end(); k++){
        int totalCards=((*k).ResourceHand.stone+(*k).ResourceHand.grain+(*k).ResourceHand.lumber+(*k).ResourceHand.wool+
                        (*k).ResourceHand.brick);
        if (totalCards>7){
            string choice;
            cout << (*k).getName() << " has " << totalCards << " resources. You must discard " << totalCards/2 << " of these.\n";
            for (int i=0;i<(totalCards/2);i++){
                cout << "Please select a resource to discard:";
                cout << "Stone= " << (*k).ResourceHand.stone << endl;
                cout << "Grain= " << (*k).ResourceHand.grain << endl;
                cout << "Lumber= " << (*k).ResourceHand.lumber << endl;
                cout << "Wool= " << (*k).ResourceHand.wool << endl;
                cout << "Brick= " << (*k).ResourceHand.brick << "\n\t";
                cin >> choice;
                do{
                    invalid=false;
                    if (choice.compare("Stone")==0)
                        (*k).ResourceHand.stone--;
                    else if (choice.compare("Grain")==0)
                        (*k).ResourceHand.grain--;
                    else if (choice.compare("Lumber")==0)
                        (*k).ResourceHand.lumber--;
                    else if (choice.compare("Wool")==0)
                        (*k).ResourceHand.wool--;
                    else if (choice.compare("Brick")==0)
                        (*k).ResourceHand.brick--;
                    else{
                        cout << "Invalid selection. Please re-enter.\n\t";
                        cin >> choice;
                        invalid=true;
                    }
                }while(invalid==true);
            }
        }
    }
    movingBandit();
}

void Catan::movingBandit(){
    bool invalid;
    cout << turnplayerList[currentPlayer].getName() << ",you may now move the bandit. Please select a hexagon to move him to.\n\t";
    string newLoc;
    int locNum;
    cin >> newLoc;
    do{
        invalid=false;
        for (int i=0;i<(int)newLoc.size();i++){
            if(isdigit(newLoc[i])==false){
                cout << "Invalid selection. Please re-enter.\n\t";
                cin >> newLoc;
                invalid=true;
                break;
            }
        }
        if (invalid==false){
            locNum=atoi(newLoc.c_str());
            if ((locNum>18)||(locNum<0)||(board.hexLayer[locNum].hasBandit==true)){
                cout << "Invalid selection. Please re-enter.\n\t";
                cin >> newLoc;
                invalid=true;
            }
        }
    }while(invalid==true);
    board.moveBandit(locNum);
    vector<int> choices;
    for (int i=0;i<6;i++){
        if(board.vertLayer[board.hexLayer[locNum].assVert[i]].occupiedBy!=NOONE&&
           board.vertLayer[board.hexLayer[locNum].assVert[i]].occupiedBy!=turnplayerList[currentPlayer].getTurn()){
           choices.push_back((int)(board.vertLayer[board.hexLayer[locNum].assVert[i]].occupiedBy));
        }
        if ((i==5)&&(choices.size()==0)){
            cout << "Nobody around for the bandit to steal from.\n";
            delay(2);
            return;
        }
    }
    cout << "Who would you like to steal from?\n";
    string thiefChoice;
    for (int i=0;i<(int)choices.size();i++)
        cout << turnplayerList[(int)(choices[i])].getName() << endl;
    cout << "\t";
    cin >> thiefChoice;
    int recChoice;
    do{
        invalid=false;
        for (int i=0;i<(int)choices.size();i++){
            if (thiefChoice.compare(turnplayerList[(int)(choices[i])].getName())==0){
                if((turnplayerList[(int)(choices[i])].ResourceHand.stone==0)&&(turnplayerList[(int)(choices[i])].ResourceHand.grain==0)&&
                   (turnplayerList[(int)(choices[i])].ResourceHand.lumber==0)&&(turnplayerList[(int)(choices[i])].ResourceHand.wool==0)&&
                   (turnplayerList[(int)(choices[i])].ResourceHand.brick==0)){
                   cout << "This player doesnt have any resources. Too Bad.";
                   delay(2);
                   return;
                }
                else{
                    timeval Time;
                    gettimeofday(&Time, NULL);
                    long timeseed=Time.tv_usec;
                    srand(timeseed);
                    do{
                        invalid=false;
                        recChoice=rand()%5;
                        if (recChoice==0){
                            if (turnplayerList[(int)(choices[i])].ResourceHand.stone==0){
                                invalid=true;
                                continue;
                            }
                            turnplayerList[(int)(choices[i])].ResourceHand.stone--;
                            turnplayerList[currentPlayer].ResourceHand.stone++;

                        }
                        else if (recChoice==1){
                            if (turnplayerList[(int)(choices[i])].ResourceHand.grain==0){
                                invalid=true;
                                continue;

                            }
                            turnplayerList[(int)(choices[i])].ResourceHand.grain--;
                            turnplayerList[currentPlayer].ResourceHand.grain++;

                        }
                        else if (recChoice==2){
                             if (turnplayerList[(int)(choices[i])].ResourceHand.lumber==0){
                                invalid=true;
                                continue;
                            }
                            turnplayerList[(int)(choices[i])].ResourceHand.lumber--;
                            turnplayerList[currentPlayer].ResourceHand.lumber++;

                        }
                        else if (recChoice==3){
                            if (turnplayerList[(int)(choices[i])].ResourceHand.wool==0){
                                invalid=true;
                                continue;
                            }
                            turnplayerList[(int)(choices[i])].ResourceHand.wool--;
                            turnplayerList[currentPlayer].ResourceHand.wool++;
                        }
                        else if (recChoice==4){
                            if (turnplayerList[(int)(choices[i])].ResourceHand.brick==0){
                                 invalid=true;
                                continue;
                            }
                            turnplayerList[(int)(choices[i])].ResourceHand.brick--;
                            turnplayerList[currentPlayer].ResourceHand.brick++;
                        }
                    }while(invalid==true);
                }
            return;
            }
            if (i==((int)choices.size()-1)){
                cout << "Invalid selection. Please re-enter.";
                cin >> thiefChoice;
                invalid=true;
            }
        }
    }while(invalid==true);
}
