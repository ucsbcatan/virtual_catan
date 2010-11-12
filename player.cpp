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
int d = 1 + rand()%7; // number between 1 and 6;
return d;
}

int Player::pickRandCard() {
int random;
srand(time(NULL)); // srand((unsigned)time(NULL));
random = rand() % 6; //number between 0 and 5;
return random;
}






