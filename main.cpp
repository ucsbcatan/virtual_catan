#include <QtCore/QCoreApplication>
#include <QtGui/QFont>
#include <iostream>
#include <vector>
#include <fstream>

#include "catan.h"

using namespace std;

 bool inMenu;
 void MainMenu();
 void NewGame();
 void LoadGame();
 void Options();
 void GameState(Catan);

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
    Catan GameProfile(i,namesIn);
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
      pair<map<int, Player>::iterator, bool> ret;
      vector<Player>::iterator it;
      map<int, Player> playerTurnList;
      int counter = 0;


      for(vector<Player>::iterator it = (GameProfile.myplayerList).begin(); it != (GameProfile.myplayerList).end(); it++) {

              cout << "\n\n" << (*it).getName() << ", type 'roll' to roll the die" << endl;
              cin.get();
              currentPlayerRoll = (*it).makeRoll();
              cout << "/nyou rolled a:" << currentPlayerRoll;
              playerTurnList.insert(pair<int, Player>(currentPlayerRoll, (*it)));
            }

       GameProfile.myplayerList.clear();
       for (map<int, Player>::iterator it2 = playerTurnList.end(); it2 != playerTurnList.begin(); it2--) {

              (it2->second).playerNum = (GameProfile.numPlayers - counter);
              GameProfile.myplayerList.push_back(it2->second);
              counter++;
          }

       //Next iteration, turn conflict resolution

       //Players 1->i place settlement down
       //Players i->1 place settlement down

       //all players recieve recourses associated with their settlements
       //(firstTurnRecourses)<-call this from Gameboard







    bool inGame = true;
    while(inGame){

        cout<<"";
        int dickslang;
        cin>>dickslang;




    }
    return;
}
