// GAMEBOARD_H
// gameboard.h
// gameboard class for virtual catan
// manages hexagon, vertex, and edge objects
#ifndef GAMEBOARD_H
#define GAMEBOARD_H
#include <vector>
#include <iostream>
using namespace std;

enum terr {DESERT, HILLS, FIELD, MOUNTAINS, PASTURE};
typedef struct{
    Hexagon(int hexNum);
    int hexId;
    terr terrType;
    vector<VERTEX> assVert; //vector of associated vertices
}HEXAGON;

typedef struct{
    Vertex(int vertNum);
    int vertId;
    vector<int> adjEdge; //vector of adjacent edges
}VERTEX;

typedef struct{
    Edge(int edgeNum);
    int edgeId;
    vector<int> assEdge; //vector of associated edges
    vector<int> adjVert; //vector of adjacent vertices
}EDGE;

class Gameboard {
 public:
  void Gameboard();
  void setTile(terr tile);
  bool hasBandit();
  int getTerrain();
  void connectHexagon();
  void findHexagon();
 private:
  vector<HEXAGON> hexLayer;
  vector<
  int id;
  int terrainEnum;
};
#endif
