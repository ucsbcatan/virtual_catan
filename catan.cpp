// catan.cpp
// implementation for catan class

#include "catan.h"
#include <stdio.h>
#include <map>
#include <vector>
#include <sys/time.h>
#include "player.h"
#include "timeFunc.h"
using namespace std;




Catan::Catan(int numPlayersIn, vector<string> namesIn) {
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
        (*it).DevHand.knightCard = 0;
        (*it).DevHand.monopolyCard = 0;
        (*it).DevHand.roadBuildingCard = 0;
        (*it).DevHand.yearOfPlentyCard = 0;
        (*it).DevHand.progressCard = 0;
        (*it).DevHand.victoryPointCard = 0;
        (*it).ResourceHand.stone=0;
        (*it).ResourceHand.grain=0;
        (*it).ResourceHand.lumber=0;
        (*it).ResourceHand.wool=0;
        (*it).ResourceHand.brick=0;
        //NOTE: gameboard is implicity initialized here
    }
}

void Catan::placeSettlement(Player currPlayer, int vertNum){
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
        cout << "settlement placed\n\n";

    }
return;
}

void Catan::placeFirstSettlement(Player currPlayer, int &vertNum){
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
        cout<<"settlement placed\n\n";
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
        cout<<"road placed\n\n";
        return;
    }
}

void Catan::placeCity(Player currPlayer, int vertNum){
    if (board.vertLayer[vertNum].occupiedBy!= currPlayer.getTurn()){
        cout << "\nYour settlement is not at this location.\nPlease select another location.\n";
        cin >> vertNum;
        placeCity(currPlayer, vertNum);
    }

    else{
        board.setCity(currPlayer.getTurn(), vertNum);
        cout << "city placed\n";
    }
}

string Catan::findLongestRoad() {
/*for (vector<Player>::iterator it = playerList.begin(); it != playerList.end(); it++) {
if ((((*it).CardHand).longestRoadCard) == 1);
// cout << (*it).getName();

}*/
    return "na";
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
            cout << "in do-while\n";
            if ((recChoice.compare("Stone")==0)){
                cout << "Choose the amount of Stone you want to give (1-" << turnplayerList[currPlayer].ResourceHand.stone <<
                        "), or enter Back:\n";
                cin >> choiceOut;
                //
                //replace following with
                //checkInt function!!!!!
                //
                revalidInputStone:
                if (isdigit(choiceOut[0])==0){
                    if (choiceOut.compare("Back")==0){
                        inTrade=false;
                        cout << "Closing trade negotiations";
                        delay(2);
                        goto endTrade;
                    }
                }
                //checking to make sure numchoice is an int, if not re-prompts for entry and re-checks
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
                cout << "Choose the amount of Grain you want to give (1-" << turnplayerList[currPlayer].ResourceHand.grain <<
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
                cout << "Choose the amount of Lumber you want to give (1-" << turnplayerList[currPlayer].ResourceHand.lumber <<
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
                cout << "Choose the amount of Wool you want to give (1-" << turnplayerList[currPlayer].ResourceHand.wool <<
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
                        cout << "Closing trade negotiations\n";
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
                cout << "Choose the amount of Brick you want to give (1-" << turnplayerList[currPlayer].ResourceHand.brick <<
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
            else{
                cout << "Invalid selection. Please re-enter type of resource you are giving. Or enter 'Back'\n";
                cin >> recChoice;
                invalid=true;
            }

        }while(invalid==true);

//        do{
            do{ //again, checking for validity
                invalid=false;
                cout << "Please enter the resource you want for your " << recChoice << ". (Stone Grain Lumber Wool or Brick):\n";
                cin >> recIn;
                if ((recIn.compare("Stone")==1) && (recIn.compare("Grain")==1) && (recIn.compare("Lumber")==1)
                    && (recIn.compare("Wool")==1) && (recIn.compare("Brick")==1) && (recIn.compare("Back"))){
                    cout << "Invalid selection. Please re-enter.\n";
                    cin >> recIn;
                    invalid=true;
                }
            }while(invalid==true);
            if (recIn.compare("Back")){
                cout << "Closing trade negotiations\n";
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
                for (int i=0;;i++){
                    if (tradeTo.compare(turnplayerList[i].getName())==0){
                        numTo=i;
                        break;
                    }
                }

                if (choiceOut.compare("Stone"))
                    typeOut = STONE;
                if (choiceOut.compare("Lumber"))
                    typeOut = LUMBER;
                if (choiceOut.compare("Grain"))
                    typeOut = GRAIN;
                if (choiceOut.compare("Wool"))
                    typeOut = WOOL;
                if (choiceOut.compare("Brick"))
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

                    cout << "You have successfully traded " << numChoiceOut << " " << choiceOut << " for "
                            << numIn << " " << recIn << ". Congratz.\n";
                    cout << "Would you like to make another trade? (Yes or No)";
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

                    cout << "You have successfully traded " << numChoiceOut << " " << choiceOut << " for "
                            << numIn << " " << recIn << ". Congratz.\n";
                    cout << "Would you like to make another trade? (Yes or No)";
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

                    cout << "You have successfully traded " << numChoiceOut << " " << choiceOut << " for "
                            << numIn << " " << recIn << ". Congratz.\n";
                    cout << "Would you like to make another trade? (Yes or No)";
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

                    cout << "You have successfully traded " << numChoiceOut << " " << choiceOut << " for "
                            << numIn << " " << recIn << ". Congratz.\n";
                    cout << "Would you like to make another trade? (Yes or No)";
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

                    cout << "You have successfully traded " << numChoiceOut << " " << choiceOut << " for "
                            << numIn << " " << recIn << ". Congratz.\n";
                    cout << "Would you like to make another trade? (Yes or No)";
                    string tradeAgain;
                    cin >> tradeAgain;
                    if (tradeAgain.compare("Yes")==0){
                        inTrade=true;
                        continue;
                    }
                }
            }while (invalid==true);




//        }while(answer.compare("Yes")==0);
            endTrade:
            inTrade=false;
    }
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
//    terr tempTerrType;
//    currDiceRoll = diceRoll(currPlayer);
//    for(vector<HEXAGON>::iterator it=board.hexLayer.begin(); it != board.hexLayer.end(); it++) {
//        tempTerrType = (*it).terrType;
//        if(currDiceRoll == (*it).yieldNum){
//            for (vector<VERTEX>::iterator it2=board.vertLayer.begin(); it2 != board.vertLayer.end(); it2++){
//                if ((*it2).occupiedBy == PLAYER0)         //add +1 resource of tempTerrType to Player0's CardHand
//                    turnplayerList[0].addRec(tempTerrType);
//                else if ((*it2).occupiedBy == PLAYER1)    //add +1 resource of tempTerrType to Player1's CardHand
//                    turnplayerList[1].addRec(tempTerrType);
//                else if ((*it2).occupiedBy == PLAYER2)    //add +1 resource of tempTerrType to Player2's CardHand
//                    turnplayerList[2].addRec(tempTerrType);
//                else if((*it2).occupiedBy == PLAYER3)    //add +1 resource of tempTerrType to Player3's CardHand
//                    turnplayerList[3].addRec(tempTerrType);
//            }
//        }
//    }

//    //check the victory points.
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
            cout << temp[i].getName() << " ";
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
    cout << "back to beginning\n";
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
            cout << "\t" << i << endl;
    }
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
    cout << "Please select from the following edges to place your road";
    for (int i=0;i<72;i++)
        if(board.validRoad((playerNum) currentPlayer, i)==0)
            cout << "\t" << i << endl;
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


