// GAMEBOARD_H
// gameboard.h
// gameboard class for virtual catan
// manages hexagon, vertex, and edge objects
#ifndef GAMEBOARD_H
#define GAMEBOARD_H
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "player.h"
using namespace std;


struct HEXAGON{
    HEXAGON (int);
    int hexId;
    terr terrType;
    bool hasBandit;
    vector<int> assVert; //vector of associated vertices
    int yieldNum;
};

struct VERTEX{
    VERTEX ();
    VERTEX (int);
    int vertId;
    vector<int> adjEdge; //vector of adjacent edges
    playerNum occupiedBy;
};

struct EDGE{
    EDGE ();
    EDGE (int);
    int edgeId;
    //vector<int> assEdge; //vector of associated edges **not using** delete some time
    vector<int> adjVert; //vector of adjacent vertices
    playerNum occupiedBy;
};

struct YIELDNUM{
    YIELDNUM (int,int, int);
    YIELDNUM (int,int);
    int num;
    HEXAGON hex1(int);
    HEXAGON hex2(int);
};

class Gameboard {
 public:
  Gameboard();
  int moveBandit(int hexNum);
  terr getTerrain(int hexId);
  int getBanditLoc();
  int validSettle(playerNum currPlayer, int vertNum);
  int validFirstSettle(playerNum currPlayer, int vertNum);
  int validRoad(playerNum currPlayer, int edgeNum);
  vector<int> getAssVert(int hexNum);
  vector<int> getAssEdge(int vertNum);
  vector<HEXAGON> hexLayer; //vector containing all hexagons
  vector<VERTEX> vertLayer; //vector containing all vetices
  void setSettle(playerNum currPlayer, int vertNum);
  void setCity(playerNum currPlayer, int vertNum);
  void setRoad(playerNum currPlayer, int edgeNum);

 private:
  void setHexLayer();
  void setVertLayer();
  void setEdgeLayer();
  void setYield();
  void setBandit();
  void assTerrain();


  vector<EDGE> edgeLayer; //vcetor containging all edges
  vector<YIELDNUM> yieldNums; //vector containing all yield numbers
  vector<terr> unassTerrain; //vector containing terrain yet to be assigned
  int desHex; //hexagon holding desert tile
  int banditLoc; //hexagon location of bandit
};
#endif
