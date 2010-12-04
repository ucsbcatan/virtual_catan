#include <QtDeclarative/qdeclarativeview.h>
#include <QtCore/QCoreApplication>
#include <QtGui/QFont>
#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include "catan.h"
#include "gameboard.h"
#include "player.h"
#include "timeFunc.h"

using namespace std;

        /*-----------------------------------*\
        |         Global Variables &          |
        |        Function Prototypes          |
        \*-----------------------------------*/

bool menuOpen;
bool inNewGame;
void MainMenu();
void NewGame();
void LoadGame();
void Options();
void GameState(Catan GameProfile);
void Turn(Catan GameProfile, bool fromLoad);
void buildRoad();
void printBoard(Catan g);
void printBoardGameState(Catan g);
vector<string> makePlayers(int);
string infO(Catan GameProfile, int a, int b);


        /*-----------------------------------*\
        |                                     |
        |     |\    /|   /\   --|-- |\  |     |
        |     | \  / |  /--\    |   | \ |     |
        |     |  \/  | /    \ --|-- |  \|     |
        |                                     |
        \*-----------------------------------*/


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //Main Menu
    menuOpen = true;



    MainMenu();

    return a.exec();
}



        /*-----------------------------------*\
        |         Main Menu (Function)        |
        \*-----------------------------------*/

void MainMenu(){

    while(menuOpen){

        cout<<"\n\nMain Menu:    Which option do you want?:\n\nNewGame\nLoadGame\nExit\n      ";
        string input;
        cin>>input;

        if (input.compare("NewGame")==0)
            NewGame();
        else if (input.compare("LoadGame")==0)
            LoadGame();
        else if (input.compare("Exit")==0){
            cout<<"\n\t**************************\n \t**THANK YOU FOR PLAYING!**\n\t**************************";
            delay(3);
            exit(0);
        }
    }
}



        /*-----------------------------------*\
        |          New Game (Function)        |
        \*-----------------------------------*/

//This is all the infor that you'll need about the New Game Function!!!


void NewGame(){

    inNewGame = true;
    while (inNewGame){
        cout<<"\nWhat kind of game do you want to start?\nQuickMatch\nBack\n      ";
        string input;
        cin>>input;
        if(input.compare("QuickMatch")==0){
            cout<<"\nHow many players? (3 or 4)\n\n";
            int numPlayers;
            cin>>numPlayers;
            while((numPlayers!=3)&&(numPlayers!=4)){
                cout << "That is an invalid selection.\nPlease enter either 3 or 4 players: \n";
                cin >>numPlayers;
            }
            vector<string> nameList=makePlayers(numPlayers);
            Catan GameProfile(numPlayers,nameList,true);
            GameState(GameProfile);
            inNewGame=false;
        }
        if(input.compare("Back")==0){
            inNewGame=false;
            }
        }
        return;
}


        /*-----------------------------------*\
        |         Load Game (Function)        |
        \*-----------------------------------*/

//This is the description about how the load game function works


void LoadGame(){
    bool inLoadGame=true;
    while(inLoadGame){
        cout<< "\nWould you like to load your saved game? <Yes or No>\n      ";
        string input;
        cin>>input;

        if(input.compare("Yes")==0){
            Catan GameProfile(false);
            Turn(GameProfile,true);
            inLoadGame=false;
        }
        else if(input.compare("No")==0){
            inLoadGame=false;
        }
        else
            cout<< "Please enter either 'Yes' or 'No':\n      ";
    }
    return;
}





        /*------------------------------------------------------------*\
        |      ___                ___   ___  _____      _____  ___     |
        |     |      /\  |\    /||     |       |    /\    |   |        |
        |     | --- /--\ | \  / ||---  |---|   |   /--\   |   |---     |
        |     |__| /    \|  \/  ||___   ___|   |  /    \  |   |___     |
        |                                                              |
        \*------------------------------------------------------------*/

//This is the description about what happens in the gamestate function


void GameState(Catan GameProfile){

      cout<<"\n\nyou made it to the gamestate!!\n\n";
      cout.flush();

      cout << "\nPlayers are: \n" << endl;
      for (int i=0;i<(int)GameProfile.myplayerList.size();i++)
          cout << GameProfile.myplayerList[i].getName() << endl;

      GameProfile.decideOrder();
      GameProfile.currentPlayer=0;
      cout << "Turn order is:\n";
      for (int i=0;i<(int)GameProfile.turnplayerList.size();i++){
          cout << GameProfile.turnplayerList[i].getName() << " is " << GameProfile.turnplayerList[i].getTurn() << endl;
      }

      delay(3);
      int hexchoice, vertchoice, edgechoice;

      for (vector<Player>::iterator k =(GameProfile.turnplayerList).begin(); k!=(GameProfile.turnplayerList).end(); k++){
          printBoard(GameProfile);
          cout << "current player: " << (*k).getName() << ", choose a hexagon (0-18) " << endl;
          cin >> hexchoice;

          cout << "choose an available vertex:\t";
          for (int i=0;i<6;i++){
              int validVal=GameProfile.board.validSettle((*k).getTurn(),GameProfile.board.hexLayer[hexchoice].assVert[i]);
              if ((validVal==0) || (validVal==3)){
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
                      cout << "LL\t";
              }
          }
          cout << "\n(to place your settlement)\t";
          for(int i = 0; i<6; i++){
              int validVal=GameProfile.board.validSettle((*k).getTurn(),GameProfile.board.hexLayer[hexchoice].assVert[i]);
               if ((validVal==0) || (validVal==3))
                  cout << GameProfile.board.getAssVert(hexchoice)[i] << "\t";
          }
          cout<<endl;
          cin >> vertchoice;
          GameProfile.placeFirstSettlement(*k, vertchoice);

          cout << "choose an available edge (to place your road):\t";
          for(int i = 0; i<(int)(GameProfile.board.getAssEdge(vertchoice).size()) ; i++){
//              int validVal=GameProfile.board.validSettle((*k).getTurn(),GameProfile.board.getAssEdge(vertchoice)[i]);
//              if ((validVal==0)||(validVal==2))
                cout<<GameProfile.board.getAssEdge(vertchoice)[i] << "\t";
          }
          cout<<endl;
          cin >> edgechoice;
          GameProfile.placeRoad(*k, edgechoice);
          cout<<endl;
      }

      cout<<"\n\ngoing backwards\n\n";

      for (vector<Player>::reverse_iterator it8 = (GameProfile.turnplayerList).rbegin(); it8 != (GameProfile.turnplayerList).rend(); it8++) {
         printBoard(GameProfile);
         cout << (*it8).getName() << ", choose a hexagon (0-18) " << endl;
         cin >> hexchoice;
         cout << "choose an available vertex:\t";

         for (int i=0;i<6;i++){
            if ((GameProfile.board.validSettle((*it8).getTurn(), GameProfile.board.getAssVert(hexchoice)[i]) == 3) ||
                (GameProfile.board.validSettle((*it8).getTurn(), GameProfile.board.getAssVert(hexchoice)[i]) == 0)){
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
                    cout << "LL\t";
            }

    }
    cout << "\n(to place your settlement)\t";
    int i=0;
    for(; i<6; i++){
        if ((GameProfile.board.validSettle((*it8).getTurn(), GameProfile.board.getAssVert(hexchoice)[i]) == 3) ||
            (GameProfile.board.validSettle((*it8).getTurn(), GameProfile.board.getAssVert(hexchoice)[i]) == 0))
        cout << GameProfile.board.getAssVert(hexchoice)[i] << "\t";
    }
    cout<<endl;
    cin >> vertchoice;
    GameProfile.placeFirstSettlement(*it8, vertchoice);
    int count;
    for (i=0, count=0 ;i<19;i++){
        for (int j=0;j<6;j++){
            if (GameProfile.board.hexLayer[i].assVert[j]==vertchoice){
                (*it8).addRec(GameProfile.board.hexLayer[i].terrType);
                count++;
                break;
            }
        }
        if (count==3)
            break;
    }
    cout << "choose an available edge (to place your road):\t";
    for(int i = 0; i<(int)(GameProfile.board.getAssEdge(vertchoice).size()) ; i++){
//        int validVal=GameProfile.board.validSettle((*k).getTurn(),GameProfile.board.getAssEdge(vertchoice)[i]);
//        if ((validVal==0)||(validVal==2))
          cout<<GameProfile.board.getAssEdge(vertchoice)[i] << "\t";
    }
    cout<<endl;
    cin >> edgechoice;
    GameProfile.placeRoad(*it8,edgechoice);
    cout<<endl;
}

      for (int i=0;i<(int)GameProfile.turnplayerList.size();i++){

         cout << "\nPlayer " << i << " received:\n";
         cout << "Stone:\t" << GameProfile.turnplayerList[i].ResourceHand.stone << endl;
         cout << "Grain:\t" << GameProfile.turnplayerList[i].ResourceHand.grain << endl;
         cout << "Lumber:\t" << GameProfile.turnplayerList[i].ResourceHand.lumber << endl;
         cout << "Wool:\t" << GameProfile.turnplayerList[i].ResourceHand.wool << endl;
         cout << "Brick:\t" << GameProfile.turnplayerList[i].ResourceHand.brick << endl;
  }
    Turn(GameProfile,false);
}




        /*---------------------------------*\
        |     _____         __              |
        |       |   |    | |  \ |\  |       |
        |       |   |    | |__/ | \ |       |
        |       |    \__/  |  \ |  \|       |
        |                                   |
        \*---------------------------------*/

//This is the description about what happens in the Turn function

void Turn(Catan GameProfile, bool fromLoad){

    cout << "Game commencing. \n";
    bool inGame = true;
    string input;
    cout.flush();

    if(fromLoad==false){
        int roll1=GameProfile.diceRoll(GameProfile.turnplayerList[0]);
        int roll2=GameProfile.diceRoll(GameProfile.turnplayerList[0]);
        int total=roll1+roll2;
        GameProfile.yield(total);
        cout << "total roll was a " << total << endl;
        GameProfile.check7(total);
    }

    while(inGame){
        cout.flush();
       //GameProfile.
        printBoard(GameProfile);
        cout << "\nCurrent Player Turn is: " << GameProfile.turnplayerList[GameProfile.currentPlayer].getName() <<" ("<<GameProfile.currentPlayer<<")"<< endl;
        cout << "\nChoose from the following list of moves:";

        cout<< "\n\nTrade\t\tBuild\t\tBuildingCosts\nBuyDev\t\tPlayDev\t\tSeeDevHand\nEndTurn\t\tSaveGame\tQuitGame\n   \t\t\t\t\t\t";
        cin>>input;
        cout<<"\n\n";
        bool invalid;
        do{
            invalid=false;
            if (input.compare("EndTurn") == 0) {
                GameProfile.endTurn();
                int roll1=GameProfile.diceRoll(GameProfile.turnplayerList[GameProfile.currentPlayer]);
                int roll2=GameProfile.diceRoll(GameProfile.turnplayerList[GameProfile.currentPlayer]);
                int total = roll1+roll2;
                GameProfile.yield(total);
                cout << "total roll was a " << total << endl;
                GameProfile.check7(total);
            }
            else if (input.compare("Trade") == 0){
                            string choice;
                            cout << "Would you like to trade with a Port or another player? (enter Port Player or Back)\n\t";
                            cin >> choice;
                            while (!(choice.compare("Port")==0)&&!(choice.compare("Player")==0)&&!(choice.compare("Back")==0)){
                                cout << "invalid selection, please re-enter.\n\t";
                                cin >> choice;
                            }
                            if (choice.compare("Port")==0)
                                GameProfile.portTrade();
                            else if (choice.compare("Player")==0)
                                GameProfile.trade();
                            else if (choice.compare("Back")==0)
                                continue;
                        }
            else if (input.compare("Build") == 0){
                cout << "What would you like to build?\n\tSettlement\n\tRoad\n\tCity\n\tBack\n\t";
                string toBuild;
                cin >> toBuild;
                bool invalidBuild;
                do{
                    invalidBuild=false;
                    if (toBuild.compare("Settlement")==0){
                        if(GameProfile.sufficientRec("Settlement"))
                            GameProfile.buildSettle();
                        else
                            cout << "you don't have enough recourses dipshit!\n\n";
                    }
                    else if (toBuild.compare("Road")==0){
                        if(GameProfile.sufficientRec("Road"))
                            GameProfile.buildRoad();
                        else
                            cout << "you don't have enough recourses dipshit!\n\n";
                    }
                    else if (toBuild.compare("City")==0){
                        if(GameProfile.sufficientRec("City"))
                            GameProfile.upCity();
                        else
                            cout << "you don't have enough recourses dipshit!\n\n";
                    }
                    else if (toBuild.compare("Back")==0){
                        continue;
                    }
                    else {
                        invalidBuild=true;
                        cout << "Invalid entry. Please re-enter selection\n";
                        cin >> toBuild;
                    }

                }while (invalidBuild==true);
            }
            else if (input.compare("PlayDev") == 0){
                int numDevs=0;
                numDevs=GameProfile.turnplayerList[GameProfile.currentPlayer].DevHand.soldierCard + GameProfile.turnplayerList[GameProfile.currentPlayer].DevHand.monopolyCard + GameProfile.turnplayerList[GameProfile.currentPlayer].DevHand.yearOfPlentyCard +
                        GameProfile.turnplayerList[GameProfile.currentPlayer].DevHand.victoryPointCard + GameProfile.turnplayerList[GameProfile.currentPlayer].DevHand.roadBuildingCard;
                            if (numDevs==0){
                                cout << "You dont have any Development Cards to play.\n";
                                continue;
                            }
                            GameProfile.playDev();
                        }
            else if (input.compare("BuyDev") == 0 ){
                if(GameProfile.sufficientRec("BuyDev")){
                    cout << "you have sufficient funds!\n";
                    GameProfile.drawfromDevDeck();
                }
                else
                    cout << "you don't have enough recourses dipshit!\n\n";
            }
            else if (input.compare("QuitGame")==0){
                cout << "Are you sure you want to leave the game? (yes or no) ";
                string decide;
                cin >> decide;
                if (decide.compare("yes") == 0){
                    cout<<"Do you want to save your game first? (yes or no) ";
                    string in;
                    cin >> in;
                    if(in.compare("yes")==0){
                        GameProfile.saveGame();
                    }
                    inGame = false;
                }
            }
            else if (input.compare("BuildingCosts")==0){
                cout<< "\n\n";
                cout<< "    A Road costs 1 LUMBER and 1 BRICK\n";
                cout<< "    A Settlement costs 1 LUMBER, 1 BRICK, 1 GRAIN, and 1 WOOL\n";
                cout<< "    A City costs 2 GRAIN and 3 STONE\n";
                cout<< "    A Development Card costs 1 GRAIN, 1 STONE, and 1 WOOL\n";
                cout<< "\n\n";
            }
            else if (input.compare("SaveGame")==0){
                GameProfile.saveGame();
            }
            else if (input.compare("SeeDevHand")==0){    //just for teeesting
                cout << "\n\n";
                cout <<"  "<<GameProfile.turnplayerList[GameProfile.currentPlayer].DevHand.soldierCard << " Soldier Cards\n";
                cout <<"  "<<GameProfile.turnplayerList[GameProfile.currentPlayer].DevHand.victoryPointCard << " Victory Point Cards\n";
                cout <<"  "<<GameProfile.turnplayerList[GameProfile.currentPlayer].DevHand.monopolyCard << " Monopoly Cards\n";
                cout <<"  "<<GameProfile.turnplayerList[GameProfile.currentPlayer].DevHand.roadBuildingCard << " Road Building Cards\n";
                cout <<"  "<<GameProfile.turnplayerList[GameProfile.currentPlayer].DevHand.yearOfPlentyCard << " Year Of Plenty Cards\n";
                cout << "\n\n";
                delay(5);
            }
            else{
                invalid=true;
                cout << "Invalid entry. Please Re-enter selection.\n   ";
                cin >> input;
            }
        }while(invalid==true);


        if (GameProfile.checksForWinner()){
            delay(3);
            inGame=false;
        }

    }
}





        /*-----------------------------------*\
        |       Make Players (Function)       |
        \*-----------------------------------*/

//This is the description about what happens in the make players function
//the above is a comment about the description
//the above is just unnecessary
//seriously stop commenting
//that last comment was hypocritical
//duly noted
//kk

vector<string> makePlayers(int numPlayers)
{

    cout<<"\nPlease enter the player names:"<<endl;
    string in;
    vector<string> namesIn;
    for(int k=0;k<numPlayers;k++){
        cout<<k+1<<". ";
        cin>>in;
        for (int i=0;i<(int)namesIn.size();i++){
            while (in==namesIn[i]){
                cout << namesIn[i] << " is already taken. Please enter a new name.\n";
                cin >> in;
            }
        }
        namesIn.push_back(in);
    }
//    cout << "names in contains " << endl;
//    for (int i=0;i<(int)namesIn.size();i++)
//        cout << namesIn[i] << " ";
return namesIn;
}







        /*-----------------------------------*\
        |        PrintBoard (Function)        |
        \*-----------------------------------*/

void printBoard(Catan g){

    cout<<"                      \\                          /"<<endl;
    cout<<"                        \\                      /"<<endl;
    cout<<"                  "<<infO(g,11,0)<<"  \\                  /    "<<infO(g,11,1)<<endl;
    cout<<"                   "<<infO(g,12,0)<<":1     "<<infO(g,1,1)<<"             "<<infO(g,1,3)<<"     "<<infO(g,12,1)<<":1    "<<infO(g,1,5)<< endl;
    cout<<"              \\           /   \\           /   \\           /   \\ " << endl;
    cout<<"                \\      "<<infO(g,2,0)<<"     "<<infO(g,3,1)<<"     "<<infO(g,2,2)<<"     "<<infO(g,3,3)<<"     "<<infO(g,2,4)<<"     "<<infO(g,3,5)<< endl;
    cout<<"                  \\   /           \\   /           \\   /           \\ "<<endl;
    cout<<"                   "<<infO(g,1,0)<<"             "<<infO(g,1,2)<<"             "<<infO(g,1,4)<<"             "<<infO(g,1,6)<<endl;
    cout<<"                    |   "<<infO(g,5,0)<<"   |   "<<infO(g,5,1)<<"   |   "<<infO(g,5,2)<<"   |     /"<<endl;
    cout<<"                   "<<infO(g,4,6)<<"      "<<infO(g,6,0)<<"     "<<infO(g,4,7)<<"      "<<infO(g,6,1)<<"     "<<infO(g,4,8)<<"      "<<infO(g,6,2)<<"     "<<infO(g,4,9)<<"  /"<<endl;
    cout<<"                    |     "<<infO(g,7,0)<<"    |     "<<infO(g,7,1)<<"    |     "<<infO(g,7,2)<<"    | /   "<<infO(g,11,2)<<endl;
    cout<<"                   "<<infO(g,1,8)<<"             "<<infO(g,1,10)<<"             "<<infO(g,1,12)<<"             "<<infO(g,1,14)<<"     "<<infO(g,12,2)<<":1"<<endl;
    cout<<"                  /   \\           /   \\           /   \\           /   \\           /"<<endl;
    cout<<"  _ _ _ _      "<<infO(g,2,10)<<"     "<<infO(g,3,11)<<"     "<<infO(g,2,12)<<"     "<<infO(g,3,13)<<"     "<<infO(g,2,14)<<"     "<<infO(g,3,15)<<"     "<<infO(g,2,16)<<"     "<<infO(g,3,17)<<"      /"<<endl;
    cout<<"          \\   /           \\   /           \\   /           \\   /           \\   /"<<endl;
    cout<<"           "<<infO(g,1,7)<<"             "<<infO(g,1,9)<<"             "<<infO(g,1,11)<<"             "<<infO(g,1,13)<<"             "<<infO(g,1,15)<<endl;
    cout<<"    "<<infO(g,11,8)<<"  |   "<<infO(g,5,3)<<"   |   "<<infO(g,5,4)<<"   |   "<<infO(g,5,5)<<"   |   "<<infO(g,5,6)<<"   |"<<endl;
    cout<<"     "<<infO(g,12,8)<<":1   "<<infO(g,4,18)<<"      "<<infO(g,6,3)<<"     "<<infO(g,4,19)<<"      "<<infO(g,6,4)<<"     "<<infO(g,4,20)<<"      "<<infO(g,6,5)<<"     "<<infO(g,4,21)<<"      "<<infO(g,6,6)<<"     "<<infO(g,4,22)<<endl;
    cout<<"            |     "<<infO(g,7,3)<<"    |     "<<infO(g,7,4)<<"    |     "<<infO(g,7,5)<<"    |     "<<infO(g,7,6)<<"    |"<<endl;
    cout<<"           "<<infO(g,1,17)<<"             "<<infO(g,1,19)<<"             "<<infO(g,1,21)<<"             "<<infO(g,1,23)<<"             "<<infO(g,1,25)<<endl;
    cout<<"  _ _ _   /   \\           /   \\           /   \\           /   \\           /   \\"<<endl;
    cout<<"       "<<infO(g,2,23)<<"     "<<infO(g,3,24)<<"     "<<infO(g,2,25)<<"     "<<infO(g,3,26)<<"     "<<infO(g,2,27)<<"     "<<infO(g,3,28)<<"     "<<infO(g,2,29)<<"     "<<infO(g,3,30)<<"     "<<infO(g,2,31)<<"     "<<infO(g,3,32)<<"      _ _ _ _"<<endl;
    cout<<"      /           \\   /           \\   /           \\   /           \\   /           \\   /"<<endl;
    cout<<"   "<<infO(g,1,16)<<"             "<<infO(g,1,18)<<"             "<<infO(g,1,20)<<"             "<<infO(g,1,22)<<"             "<<infO(g,1,24)<<"             "<<infO(g,1,26)<<endl;
    cout<<"    |   "<<infO(g,5,7)<<"   |   "<<infO(g,5,8)<<"   |   "<<infO(g,5,9)<<"   |   "<<infO(g,5,10)<<"   |   "<<infO(g,5,11)<<"   |   "<<infO(g,11,3)<<endl;
    cout<<"   "<<infO(g,4,33)<<"      "<<infO(g,6,7)<<"     "<<infO(g,4,34)<<"      "<<infO(g,6,8)<<"     "<<infO(g,4,35)<<"      "<<infO(g,6,9)<<"     "<<infO(g,4,36)<<"      "<<infO(g,6,10)<<"     "<<infO(g,4,37)<<"      "<<infO(g,6,11)<<"     "<<infO(g,4,38)<<"   "<<infO(g,12,3)<<":1"<<endl;
    cout<<"    |     "<<infO(g,7,7)<<"    |     "<<infO(g,7,8)<<"    |     "<<infO(g,7,9)<<"    |     "<<infO(g,7,10)<<"    |     "<<infO(g,7,11)<<"    |"<<endl;
    cout<<"   "<<infO(g,1,27)<<"             "<<infO(g,1,29)<<"             "<<infO(g,1,31)<<"             "<<infO(g,1,33)<<"             "<<infO(g,1,35)<<"             "<<infO(g,1,37)<<endl;
    cout<<"      \\           /   \\           /   \\           /   \\           /   \\           /   \\ _ _ _ _"<<endl;
    cout<<"  _ _ _"<<infO(g,3,39)<<"     "<<infO(g,2,40)<<"     "<<infO(g,3,41)<<"     "<<infO(g,2,42)<<"     "<<infO(g,3,43)<<"     "<<infO(g,2,44)<<"     "<<infO(g,3,45)<<"     "<<infO(g,2,46)<<"     "<<infO(g,3,47)<<"     "<<infO(g,2,48)<<""<<endl;
    cout<<"          \\   /           \\   /           \\   /           \\   /           \\   /    "<<endl;
    cout<<"           "<<infO(g,1,28)<<"             "<<infO(g,1,30)<<"             "<<infO(g,1,32)<<"             "<<infO(g,1,34)<<"             "<<infO(g,1,36)<<endl;
    cout<<"    "<<infO(g,11,7)<<"  |   "<<infO(g,5,12)<<"   |   "<<infO(g,5,13)<<"   |   "<<infO(g,5,14)<<"   |   "<<infO(g,5,15)<<"   |"<<endl;
    cout<<"     "<<infO(g,12,7)<<":1   "<<infO(g,4,49)<<"      "<<infO(g,6,12)<<"     "<<infO(g,4,50)<<"      "<<infO(g,6,13)<<"     "<<infO(g,4,51)<<"      "<<infO(g,6,14)<<"     "<<infO(g,4,52)<<"      "<<infO(g,6,15)<<"     "<<infO(g,4,53)<<"        ________________"<<endl;
    cout<<"            |     "<<infO(g,7,12)<<"    |     "<<infO(g,7,13)<<"    |     "<<infO(g,7,14)<<"    |     "<<infO(g,7,15)<<"    |        | Player:        |"<<endl;
    cout<<"           "<<infO(g,1,38)<<"             "<<infO(g,1,40)<<"             "<<infO(g,1,42)<<"             "<<infO(g,1,44)<<"             "<<infO(g,1,46)<<"       |----------------|"<<endl;
    cout<<"  _ _ _ _ /   \\           /   \\           /   \\           /   \\           /   \\      |   "<<infO(g,8,0)<<"|"<<endl;
    cout<<"               "<<infO(g,3,54)<<"     "<<infO(g,2,55)<<"     "<<infO(g,3,56)<<"     "<<infO(g,2,57)<<"     "<<infO(g,3,58)<<"     "<<infO(g,2,59)<<"     "<<infO(g,3,60)<<"     "<<infO(g,2,61)<<"      \\    |   ("<<g.currentPlayer<<")          |"<<endl;
    cout<<"                  \\   /           \\   /           \\   /           \\   /   "<<infO(g,11,4)<<"  \\  |________________|"<<endl;
    cout<<"                   "<<infO(g,1,39)<<"             "<<infO(g,1,41)<<"             "<<infO(g,1,43)<<"             "<<infO(g,1,45)<<"     "<<infO(g,12,4)<<":1       | Resources:     | "<<endl;
    cout<<"                    |   "<<infO(g,5,16)<<"   |   "<<infO(g,5,17)<<"   |   "<<infO(g,5,18)<<"   | \\              |----------------|"<<endl;
    cout<<"                   "<<infO(g,4,62)<<"      "<<infO(g,6,16)<<"     "<<infO(g,4,63)<<"      "<<infO(g,6,17)<<"     "<<infO(g,4,64)<<"      "<<infO(g,6,18)<<"     "<<infO(g,4,65)<<"  \\            |   Stone:  "<<infO(g,9,0)<<"    |"<<endl;
    cout<<"                    |     "<<infO(g,7,16)<<"    |     "<<infO(g,7,17)<<"    |     "<<infO(g,7,18)<<"    |     \\          |   Grain:  "<<infO(g,9,1)<<"    |"<<endl;
    cout<<"                   "<<infO(g,1,47)<<"             "<<infO(g,1,49)<<"             "<<infO(g,1,51)<<"             "<<infO(g,1,53)<<"               |   Lumber: "<<infO(g,9,2)<<"    |"<<endl;
    cout<<"                  /   \\           /   \\           /   \\           /                  |   Wool:   "<<infO(g,9,3)<<"    |"<<endl;
    cout<<"                /      "<<infO(g,3,66)<<"     "<<infO(g,2,67)<<"     "<<infO(g,3,68)<<"     "<<infO(g,2,69)<<"     "<<infO(g,3,70)<<"     "<<infO(g,2,71)<<"                   |   Brick:  "<<infO(g,9,4)<<"    |"<<endl;
    cout<<"              /   "<<infO(g,11,6)<<"  \\   /           \\   /   "<<infO(g,11,5)<<"  \\   /                      |----------------|"<<endl;
    cout<<"                   "<<infO(g,12,6)<<":1     "<<infO(g,1,48)<<"             "<<infO(g,1,50)<<"     "<<infO(g,12,5)<<":1     "<<infO(g,1,52)<<"                       | VictoryPts: "<<infO(g,10,0)<<"  |"<<endl;
    cout<<"                          /                   \\                                      |________________|"<<endl;
    cout<<"                        /                       \\"<<endl;
    cout<<"                      /                           \\"<<endl;
    cout<<endl;
}

void printBoardGameState(Catan g){
    return;
}




        /*-----------------------------------*\
        |       infO (helper function)        |
        \*-----------------------------------*/

string infO(Catan GameProfile, int a, int b){

    string result;

    if(a==1){             //a vertex
        if(GameProfile.board.vertLayer[b].occupiedBy==NOONE)
            result = " o ";
        else if(GameProfile.board.vertLayer[b].occupiedBy==PLAYER0){
            if(GameProfile.board.vertLayer[b].occByType==1)
                result = "-0-";
            else
                result = "%0%";
        }
        else if(GameProfile.board.vertLayer[b].occupiedBy==PLAYER1){
            if(GameProfile.board.vertLayer[b].occByType==1)
                result = "-1-";
            else
                result = "%1%";
        }
        else if(GameProfile.board.vertLayer[b].occupiedBy==PLAYER2){
            if(GameProfile.board.vertLayer[b].occByType==1)
                result = "-2-";
            else
                result = "%2%";
        }
        else if(GameProfile.board.vertLayer[b].occupiedBy==PLAYER3){
            if(GameProfile.board.vertLayer[b].occByType==1)
                result = "-3-";
            else
                result = "%3%";
        }
    }

    else if(a==2){        //a forward slash edge
        if(GameProfile.board.edgeLayer[b].occupiedBy==NOONE)
            result = " / ";
        else if(GameProfile.board.edgeLayer[b].occupiedBy==PLAYER0)
            result = " 0 ";
        else if(GameProfile.board.edgeLayer[b].occupiedBy==PLAYER1)
            result = " 1 ";
        else if(GameProfile.board.edgeLayer[b].occupiedBy==PLAYER2)
            result = " 2 ";
        else if(GameProfile.board.edgeLayer[b].occupiedBy==PLAYER3)
            result = " 3 ";
    }

    else if(a==3){        //a backward slash edge
        if(GameProfile.board.edgeLayer[b].occupiedBy==NOONE)
            result = " \\ ";
        else if(GameProfile.board.edgeLayer[b].occupiedBy==PLAYER0)
            result = " 0 ";
        else if(GameProfile.board.edgeLayer[b].occupiedBy==PLAYER1)
            result = " 1 ";
        else if(GameProfile.board.edgeLayer[b].occupiedBy==PLAYER2)
            result = " 2 ";
        else if(GameProfile.board.edgeLayer[b].occupiedBy==PLAYER3)
            result = " 3 ";
    }

    else if(a==4){        //a straight line edge
        if(GameProfile.board.edgeLayer[b].occupiedBy==NOONE)
            result = " | ";
        else if(GameProfile.board.edgeLayer[b].occupiedBy==PLAYER0)
            result = " 0 ";
        else if(GameProfile.board.edgeLayer[b].occupiedBy==PLAYER1)
            result = " 1 ";
        else if(GameProfile.board.edgeLayer[b].occupiedBy==PLAYER2)
            result = " 2 ";
        else if(GameProfile.board.edgeLayer[b].occupiedBy==PLAYER3)
            result = " 3 ";
    }

    else if(a==5){        //a terrtype
        if(GameProfile.board.getTerrain(b)==HILLS)
            result = "  HILLS  ";
        else if(GameProfile.board.getTerrain(b)==FIELD)
            result = "  FIELD  ";
        else if(GameProfile.board.getTerrain(b)==FOREST)
            result = " FOREST  ";
        else if (GameProfile.board.getTerrain(b)==MOUNTAINS)
            result = "MOUNTAINS";
        else if (GameProfile.board.getTerrain(b)==PASTURE)
            result = " PASTURE ";
        else if (GameProfile.board.getTerrain(b)==DESERT)
            result = " DESERT  ";
    }

    else if(a==6){        //a yieldnum
        if(GameProfile.board.hexLayer[b].yieldNum==2)
            result = "2 ";
        else if(GameProfile.board.hexLayer[b].yieldNum==3)
            result = "3 ";
        else if(GameProfile.board.hexLayer[b].yieldNum==4)
            result = "4 ";
        else if(GameProfile.board.hexLayer[b].yieldNum==5)
            result = "5 ";
        else if(GameProfile.board.hexLayer[b].yieldNum==6)
            result = "6 ";
        else if(GameProfile.board.hexLayer[b].yieldNum==7)
            result = "  ";
        else if(GameProfile.board.hexLayer[b].yieldNum==8)
            result = "8 ";
        else if(GameProfile.board.hexLayer[b].yieldNum==9)
            result = "9 ";
        else if(GameProfile.board.hexLayer[b].yieldNum==10)
            result = "10";
        else if(GameProfile.board.hexLayer[b].yieldNum==11)
            result = "11";
        else if(GameProfile.board.hexLayer[b].yieldNum==12)
            result = "12";
    }

    else if(a==7){        //bandit location
        if(GameProfile.board.hexLayer[b].hasBandit==true)
            result = "bandit";
        else if(GameProfile.board.hexLayer[b].hasBandit==false)
            result = "      ";
    }

    else if(a==8){        //Player name instance
        string datName = GameProfile.turnplayerList[GameProfile.currentPlayer].getName();
        int nameSize = datName.size();

        if (nameSize<14){
            int k = 13-nameSize;
            for(int i=0; i<k; i++){
                datName.push_back(' ');
                }
            }

        else{
            datName.resize(13);
            }

    result = datName;
    }

    else if(a==9){        //Player's recourse value
        stringstream ss;
        if(b==0)
            ss << GameProfile.turnplayerList[GameProfile.currentPlayer].ResourceHand.stone;
        if(b==1)
            ss << GameProfile.turnplayerList[GameProfile.currentPlayer].ResourceHand.grain;
        if(b==2)
            ss << GameProfile.turnplayerList[GameProfile.currentPlayer].ResourceHand.lumber;
        if(b==3)
            ss << GameProfile.turnplayerList[GameProfile.currentPlayer].ResourceHand.wool;
        if(b==4)
            ss << GameProfile.turnplayerList[GameProfile.currentPlayer].ResourceHand.brick;
        result = ss.str();
    }

    else if(a==10){       //Player's victory point value ********FAKE************
        stringstream ss;
        ss << GameProfile.turnplayerList[GameProfile.currentPlayer].victoryPoints;
        result = ss.str();
    }

    else if (a==11){      //Port's type
        if(GameProfile.board.ports[b].type==0)
            result = "Stone ";
        if(GameProfile.board.ports[b].type==1)
            result = "Grain ";
        if(GameProfile.board.ports[b].type==2)
            result = "Lumber";
        if(GameProfile.board.ports[b].type==3)
            result = "Wool  ";
        if(GameProfile.board.ports[b].type==4)
            result = "Brick ";
        if(GameProfile.board.ports[b].type==5)
            result = "      ";
    }

    else if (a==12){      //for Ports, whether it is 2:1 or 3:1
        if(GameProfile.board.ports[b].type==5)
            result = "3";
        else
            result = "2";
    }
    return result;
}
