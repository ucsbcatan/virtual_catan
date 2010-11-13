#include <QtCore/QCoreApplication>
#include <QtGui/QFont>
#include <iostream>
#include <vector>
#include <fstream>

#include "catan.h"
#include "gameboard.h"

using namespace std;

 bool inMenu;
 void MainMenu();
 void NewGame();
 void LoadGame();
 void Options();
 void GameState(Catan);
 void Trade(Catan GameProfile, vector<Player> playerList, int numPlayers, int currentPlayer);



int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //Main Menu
    inMenu = true;
    MainMenu();

    cout<<"\nthank-you for playing!";
    return a.exec();
}



void MainMenu(){

    while(inMenu){

        //This should be replaced with GUI main menu and Event handler for
        //each Menu Option {NewGame,LoadGame,Options,Exit}

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
            inMenu=false;

    }
}



void NewGame(){

    //future iteration will load NewGame menu and then enter idle state
    bool inNewGame = true;

    while (inNewGame){
    cout<<"\nWhat kind of game do you want to start?\nQuickMatch\nCustomGame\nBack\n      ";
    string input;
    cin>>input;



    if(input.compare("QuickMatch")==0){            //these three will eventually be QTevents
    cout<<"\nHow many players? (1-4)\n\n"; int i;
    cin>>i;
    cout<<"\nPlease enter the player names:"<<endl;
    string in;
    vector<string> namesIn;
    for(int k=1;k<=i;k++){
        cout<<k<<". ";
        cin>>in;
        namesIn.push_back(in);
    }
   //  cout << "flag1" << endl;
    Catan GameProfile(i,namesIn);
    // cout << "flag2" << endl;
    GameState(GameProfile);
    }




    if(input.compare("CustomGame")==0){

    }
    if(input.compare("Back")==0){
    inNewGame=false;
    }
    }
    return;
}

void LoadGame(){
    return;
}

void Options(){
    //
    //
    return;
}


void GameState(Catan GameProfile){

      cout<<"\n\nyou made it to the gamestate!!\n\n";
      cout.flush();
      int currentPlayerRoll; // integer player rolled
      string nameOfMaxPlayer;
      int maxRolled = 0; // maximum number rolled
      string inroll;
      //vector<Player> turnPlayerList;
      int counter = 0;

      cout << "players are: " << endl;
      for (int i=0;i<3;i++)
          cout << GameProfile.myplayerList[i].getName() << endl;
      for (vector<Player>::iterator it = (GameProfile.myplayerList).begin(); it != (GameProfile.myplayerList).end(); it++) {
          cout << "\n\n" << (*it).getName() << ", type 'roll' to roll the die" << endl;
          cin >> inroll;
          currentPlayerRoll = (*it).makeRoll();
          cout << "you rolled a " << currentPlayerRoll << endl;
          if (currentPlayerRoll > maxRolled) {
              maxRolled = currentPlayerRoll;
              GameProfile.turnplayerList.insert(GameProfile.turnplayerList.begin(),*it);
          }

          if (currentPlayerRoll == maxRolled ) {
              counter++;

              GameProfile.turnplayerList.insert(GameProfile.turnplayerList.begin()+counter, *it);
          }

          if (currentPlayerRoll < maxRolled) {
              GameProfile.turnplayerList.push_back(*it);
          }
                    cout << "turn order is " << (*it).getName() << endl;
      }

       //Players 1->i place settlement down////////////////////////////////////////////////////////////////////

       cout << "\nHexagon Number" << "\t\t" << "Terrain" << "\n";
       terr myTerr;
       for(int i = 0; i<19 ; i++){
           myTerr = GameProfile.board.getTerrain(i);
           cout << i << "\t";

           if (myTerr == 0)
               cout << "HILLS\t";
           else if (myTerr == 1)
               cout << "FIELD\t";
           else if (myTerr == 2)
               cout << "FOREST\t";
           else if (myTerr == 3)
               cout << "MOUNTAINS\t";
           else if (myTerr == 4)
               cout << "PASTURE\t";
           else if (myTerr == 5)
               cout << "DESERT\t";

           cout<<endl;
       }
int hexchoice, vertchoice, edgechoice;
for(vector<Player>::iterator k =(GameProfile.turnplayerList).begin(); k!=(GameProfile.turnplayerList).end(); k++){

           cout << "current player: " << (*k).getName() << ", choose a hexagon (0-18) " << endl;
           cin >> hexchoice;

           cout << "choose an available vertex: UL Tp UR LR Bt LL" << endl;
           cout << "                            ";
           for(int poop = 0; poop<6; poop++)
               cout<< GameProfile.board.getAssVert(hexchoice)[poop] << " ";
           cout<<endl;
           cin >> vertchoice;
           GameProfile.placeFirstSettlement(*k, vertchoice);

           cout << "choose an available edge: ";
           for(int poop = 0; poop<(GameProfile.board.getAssEdge(vertchoice).size()) ; poop++)
               cout<<GameProfile.board.getAssEdge(vertchoice)[poop] << " ";
           cout<<endl;
           cin >> edgechoice;
           GameProfile.placeRoad(*k,edgechoice);

}
//Players i->1 place settlement down
cout<<"\n\ngoing backwards\n\n";
for (vector<Player>::reverse_iterator it8 = (GameProfile.turnplayerList).rbegin(); it8 != (GameProfile.turnplayerList).rend(); it8++) {
    cout << (*it8).getName() << ", choose a hexagon (0-18) " << endl;
    cin >> hexchoice;

    cout << "choose an available vertex:   UL Tp UR LR Bt LL" << endl;
    cout << "(to place your settlement)    ";
    for(int poop = 0; poop<6; poop++)
        cout<< GameProfile.board.getAssVert(hexchoice)[poop] << " ";
    cout<<endl;
    cin >> vertchoice;
    GameProfile.placeFirstSettlement(*it8, vertchoice);

    cout << "choose an available edge (to place your road: ";
    for(int poop = 0; poop<(GameProfile.board.getAssEdge(vertchoice).size()) ; poop++)
        cout<<GameProfile.board.getAssEdge(vertchoice)[poop] << " ";
    cout<<endl;
    cin >> edgechoice;
    GameProfile.placeRoad(*it8,edgechoice);
    cout<<endl;
}


       //all players recieve recourses associated with their settlements
       //(firstTurnResources)<-call this from Gameboard
    GameProfile.firstYield();
    bool inGame = true;
    string input;
    int nextPlayer = 0;
    int amountPlayers = GameProfile.numPlayers;
    int currentPlayer = 0;
    while(inGame){
        GameProfile.yield();
        currentPlayer = nextPlayer;
        cout << "Current Player Turn is: " << GameProfile.turnplayerList[currentPlayer].getName() << endl;
        cout << "\nUse the following commands to finish your turn:";

        cout<< "\n\nTrade\tBuild\tPlayDev\nBuy\tEndTurn\n   ";
        cin>>input;

        if (input.compare("EndTurn") == 0) {
            currentPlayer++;
            nextPlayer = currentPlayer % amountPlayers;
        }
        if (input.compare("Trade") == 0)
            Trade(GameProfile, GameProfile.turnplayerList, amountPlayers, currentPlayer);

        if (input.compare("Build") == 0)
            ;
        if (input.compare("PlayDev") == 0)
            ;
        if (input.compare("Buy") == 0 )
            ;
    }
return;
}







void Trade(Catan GameProfile, vector<Player> playerList, int numPlayers, int currentPlayer) {
    string playerInput;
    cout << playerList[currentPlayer].getName() << ", who would you like to trade with?" << endl;
    for (int j=0; j<numPlayers; j++) {
        if (playerList[j].getName() != playerList[currentPlayer].getName())
           cout << playerList[j].getName();
    }
    cin>>playerInput;
    for (int k=0; k<numPlayers; k++) {
        if (playerInput.compare(playerList[k].getName()) == 0)
            GameProfile.trade(playerList[currentPlayer],playerList[k]);
    }
}


