#include <QtCore/QCoreApplication>
#include <QtGui/QFont>
#include <iostream>
#include <vector>
#include <fstream>
#include "catan.h"
#include "gameboard.h"
#include "player.h"

using namespace std;

        /*-----------------------------------*\
        |         Global Variables &          |
        |        Function Prototypes          |
        \*-----------------------------------*/

bool menuOpen;
void MainMenu();
void NewGame();
void LoadGame();
void Options();
void GameState(Catan);
void Trade(Catan GameProfile, vector<Player> playerList, int numPlayers, int currentPlayer);
vector<string> makePlayers(int);


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

    cout<<"\nthank-you for playing!";
    return a.exec();
}



        /*-----------------------------------*\
        |         Main Menu (Function)        |
        \*-----------------------------------*/

void MainMenu(){

    while(menuOpen){

        cout<<"\n\nMain Menu:    Which option do you want?:\n\nNewGame\nLoadGame\nOptions\nExit\n      ";
        string input;
        cin>>input;

        if (input.compare("NewGame")==0)
            NewGame();
        if (input.compare("LoadGame")==0)
            LoadGame();
        if (input.compare("Options")==0)
            Options();
        if (input.compare("Exit")==0)
            menuOpen=false;

    }
}



        /*-----------------------------------*\
        |          New Game (Function)        |
        \*-----------------------------------*/

//This is all the infor that you'll need about the New Game Function!!!


void NewGame(){

    bool inNewGame = true;
    while (inNewGame){
        cout<<"\nWhat kind of game do you want to start?\nQuickMatch\nCustomGame\nBack\n      ";
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
            Catan GameProfile(numPlayers,nameList);
            GameState(GameProfile);
        }

        if(input.compare("CustomGame")==0){
            //unimplemented
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
    return;
}



        /*-----------------------------------*\
        |         Options (Function)          |
        \*-----------------------------------*/

//THis is the description about how the options feature works


void Options(){
    //
    //
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
      cout << "Turn order is:\n";
      for (int i=0;i<(int)GameProfile.turnplayerList.size();i++){
          cout << GameProfile.turnplayerList[i].getName() << " is " << (i+1) << endl;
      }

      cout << "\nHexagon Number" << "\t\t" << "Terrain" << "\t\tYield Number\n";
      terr myTerr;
      for(int i = 0; i<19 ; i++){
          myTerr = GameProfile.board.getTerrain(i);
          cout << "\t" << i << "\t\t";

          if (myTerr == 0)
              cout << "HILLS    \t\t";
          else if (myTerr == 1)
              cout << "FIELD    \t\t";
          else if (myTerr == 2)
              cout << "FOREST   \t\t";
          else if (myTerr == 3)
              cout << "MOUNTAINS\t\t";
          else if (myTerr == 4)
              cout << "PASTURE  \t\t";
          else if (myTerr == 5)
              cout << "DESERT   \t\t";
          cout << GameProfile.board.hexLayer[i].yieldNum;
          cout<<endl;
      }

      int hexchoice, vertchoice, edgechoice;

      for (vector<Player>::iterator k =(GameProfile.turnplayerList).begin(); k!=(GameProfile.turnplayerList).end(); k++){

          cout << "current player: " << (*k).getName() << ", choose a hexagon (0-18) " << endl;
          cin >> hexchoice;

          cout << "choose an available vertex:\t";
          for (int i=0;i<6;i++){
              if (GameProfile.board.vertLayer[GameProfile.board.getAssVert(hexchoice)[i]].occupiedBy==NOONE){
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
              if (GameProfile.board.vertLayer[GameProfile.board.getAssVert(hexchoice)[i]].occupiedBy==NOONE)
              cout << GameProfile.board.getAssVert(hexchoice)[i] << "\t";
          }
          cout<<endl;
          cin >> vertchoice;
          GameProfile.placeFirstSettlement(*k, vertchoice);

          cout << "choose an available edge:\t";
          for(int i = 0; i<(int)(GameProfile.board.getAssEdge(vertchoice).size()) ; i++)
              cout<<GameProfile.board.getAssEdge(vertchoice)[i] << "\t";
          cout<<endl;
          cin >> edgechoice;
          GameProfile.placeRoad(*k, edgechoice);
}

      cout<<"\n\ngoing backwards\n\n";

      for (vector<Player>::reverse_iterator it8 = (GameProfile.turnplayerList).rbegin(); it8 != (GameProfile.turnplayerList).rend(); it8++) {

         cout << (*it8).getName() << ", choose a hexagon (0-18) " << endl;
         cin >> hexchoice;
         cout << "choose an available vertex:\t";

         for (int i=0;i<6;i++){
            if (GameProfile.board.vertLayer[GameProfile.board.getAssVert(hexchoice)[i]].occupiedBy==NOONE){
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
        if (GameProfile.board.vertLayer[GameProfile.board.getAssVert(hexchoice)[i]].occupiedBy==NOONE)
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
    for(int i = 0; i<(int)(GameProfile.board.getAssEdge(vertchoice).size()) ; i++)
        cout<< GameProfile.board.getAssEdge(vertchoice)[i] << "\t";
    cout<<endl;
    cin >> edgechoice;
    GameProfile.placeRoad(*it8,edgechoice);
    cout<<endl;
}

      for (int i=0;i<GameProfile.turnplayerList.size();i++){

         cout << "\nPlayer " << i << " received:\n";
         cout << "Stone:\t" << GameProfile.turnplayerList[i].ResourceHand.stone << endl;
         cout << "Grain:\t" << GameProfile.turnplayerList[i].ResourceHand.grain << endl;
         cout << "Lumber:\t" << GameProfile.turnplayerList[i].ResourceHand.lumber << endl;
         cout << "Wool:\t" << GameProfile.turnplayerList[i].ResourceHand.wool << endl;
         cout << "Brick:\t" << GameProfile.turnplayerList[i].ResourceHand.brick << endl;
}


    bool inGame = true;
    string input;
    int nextPlayer = 0;
    int amountPlayers = GameProfile.numPlayers;
    int currentPlayer = 0;
    while(inGame){
        //GameProfile.yield();
        currentPlayer = nextPlayer;
        cout << "\nCurrent Player Turn is: " << GameProfile.turnplayerList[currentPlayer].getName() << endl;
        cout << "\nUse the following commands to finish your turn:";

        cout<< "\n\nTrade\tBuild\tPlayDev\nBuy\tEndTurn\tQuitGame\n   ";
        cin>>input;

        if (input.compare("EndTurn") == 0) {
            currentPlayer++;
            nextPlayer = currentPlayer % amountPlayers;
        }
        if (input.compare("Trade") == 0)
            //Trade(GameProfile, GameProfile.turnplayerList, amountPlayers, currentPlayer);

        if (input.compare("Build") == 0)
            ;
        if (input.compare("PlayDev") == 0)
            ;
        if (input.compare("Buy") == 0 )
            ;
        if (input.compare("QuitGame")==0){
            inGame = false;
            menuOpen = false;
        }
    }
}







//void Trade(Catan GameProfile, vector<Player> playerList, int numPlayers, int currentPlayer) {
//    string playerInput;
//    cout << playerList[currentPlayer].getName() << ", who would you like to trade with?" << endl;
//    for (int j=0; j<numPlayers; j++) {
//        if (playerList[j].getName() != playerList[currentPlayer].getName())
//           cout << playerList[j].getName();
//    }
//    cin>>playerInput;
//    for (int k=0; k<numPlayers; k++) {
//        if (playerInput.compare(playerList[k].getName()) == 0)
//            GameProfile.trade(playerList[currentPlayer],playerList[k]);
//    }




        /*-----------------------------------*\
        |       Make Players (Function)       |
        \*-----------------------------------*/

//This is the description about what happens in the make players function


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
    cout << "names in contains " << endl;
    for (int i=0;i<(int)namesIn.size();i++)
        cout << namesIn[i] << " ";
return namesIn;
}




