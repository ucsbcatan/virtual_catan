// player.cpp
#include "player.h"


Player::Player() {

}

Player::Player(string name) {
playerName = name;
}

void Player::setScore(int currentScore) {
//score = currentScore;
return;
}



int Player::makeRoll() {
srand(time(NULL)); //srand((unsigned)time(NULL));
int d = 1 + rand()%6; // number between 1 and 6;
return d;
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
        CardHand.brickCard = CardHand.brickCard + 1;
    else if (playerCard == GRAIN)
        (CardHand.grainCard)++;
    else if (playerCard == LUMBER)
        (CardHand.lumberCard)++;
    else if (playerCard == STONE)
        (CardHand.stoneCard)++;
    else if (playerCard == WOOL)
        (CardHand.woolCard)++;
    return;
}

void Player::recOut(resourceType playerCard) {
   if (playerCard == BRICK)
       (CardHand.brickCard)--;
   else if (playerCard == GRAIN)
       (CardHand.grainCard)--;
   else if (playerCard == LUMBER)
       (CardHand.lumberCard)--;
   else if (playerCard == STONE)
       (CardHand.stoneCard)--;
   else if (playerCard == WOOL)
       (CardHand.woolCard)--;
    return;
}

void Player::addRec(terr terrType){
    if(terrType == HILLS)
        (CardHand.brickCard)++;
    else if (terrType == FIELD)
        (CardHand.grainCard)++;
    else if (terrType = FOREST)
        (CardHand.lumberCard)++;
    else if (terrType = MOUNTAINS)
        (CardHand.stoneCard)++;
    else if (terrType = PASTURE)
        (CardHand.woolCard)++;
    //else if (terrType = DESERT)
    return;
}
