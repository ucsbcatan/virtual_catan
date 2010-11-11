// catan.h
// root base class for Virtual catan
#ifndef _CATAN_H
#define _CATAN_H

//#include "player.h"
#include <iostream>
#include <vector>
#include <map>
using namespace std;

class Catan {
 public :
  Catan();
  Catan(int numPlayersIn, vector<string> namesIn);
 // map<int,string> currentScore();
  map<int,string> decideTurn(vector<string> names);
  void printPlayerName();
  int currentTime(int clockID);
  int makeRoll();
  void saveGame();
  int getScore();
  void promptPlayer();
  //player declareWinner(int playerID);
  
 protected:
  // int getScore();
  // void setScore(int point, player myPlayer); // can also us player id??
 
 private:
  int clockID;
  int numPlayers;
  vector<string> playerList;
};

#endif
