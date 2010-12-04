// player.cpp
#include "player.h"


Player::Player() {

}

Player::Player(string name) {
playerName = name;
turnNum=NOONE;
victoryPoints = 0;
}

void Player::setScore(int currentScore) {
//score = currentScore;
return;
}

int Player::pickRandCard() {
    int random;
    srand(time(NULL)); // srand((unsigned)time(NULL));
    random = rand() % 6; //number between 0 and 5;
    return random;
}

string Player::getName() {
    return playerName;
}

void Player::recIn(resourceType playerCard) {
    if (playerCard == BRICK)
        ResourceHand.brick++;
    else if (playerCard == GRAIN)
        (ResourceHand.grain)++;
    else if (playerCard == LUMBER)
        (ResourceHand.lumber)++;
    else if (playerCard == STONE)
        (ResourceHand.stone)++;
    else if (playerCard == WOOL)
        (ResourceHand.wool)++;
    return;
}

void Player::recOut(resourceType playerCard) {
   if (playerCard == BRICK)
       (ResourceHand.brick)--;
   else if (playerCard == GRAIN)
       (ResourceHand.grain)--;
   else if (playerCard == LUMBER)
       (ResourceHand.lumber)--;
   else if (playerCard == STONE)
       (ResourceHand.stone)--;
   else if (playerCard == WOOL)
       (ResourceHand.wool)--;
    return;
}

void Player::addRec(terr terrType){
    if(terrType == HILLS)
        (ResourceHand.brick)++;
    else if (terrType == FIELD)
        (ResourceHand.grain)++;
    else if (terrType == FOREST)
        (ResourceHand.lumber)++;
    else if (terrType == MOUNTAINS)
        (ResourceHand.stone)++;
    else if (terrType == PASTURE)
        (ResourceHand.wool)++;
    //else if (terrType = DESERT)
    return;
}

playerNum Player::getTurn(){
    return turnNum;
}

void Player::setTurn(playerNum num){
    turnNum=num;
}

void Player::printHand(){

}

