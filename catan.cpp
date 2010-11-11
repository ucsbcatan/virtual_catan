// catan.cpp
// implementation for catan class

#include "catan.h"
#include <cstdlib>
Catan::Catan(){
  // do nothing.
}

Catan::Catan(int numPlayersIn, vector<string> namesIn) {
  // initialize clock
  // load vector of Player objects
  for (vector<string>::iterator it=namesIn.begin(); it != namesIn.end(); it++)
    {
      playerList.push_back(*it);
			   
 
    }	        
}

void Catan::printPlayerName() {
  for (vector<string>::iterator it = playerList.begin(); it != playerList.end(); it++) {

    cout << (*it) << endl;
    } 
}

/*
map<int, string> Catan::currentScore(player myPlayer) {
  // here print set string of players and score to screen
  
}
*/

int Catan::makeRoll() {
  //srand((unsigned)time(NULL));
  int d = 1 + rand() % 6;
  return d;
}


map<int, string> Catan::decideTurn(vector<string> names) {
  int turn;
  map<int, string> playerList;
  vector<string>::iterator it;
  
  
  
  for (it = names.begin(); it < names.end(); it++) {
    //Player player(*it);
    
  }
  
  
  return playerList;
}
