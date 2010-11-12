// deck.h
// deck class for Virtual Catan

#ifndef _DECK_H
#define _DECK_H

#include <iostream>
#include "card.h"
include namespace std;

class Deck {
 public:
  card drawCard(); // player class ????
  void discardCard(); // take from deck
 private:
  int ownerID;
  int amountCards;
  bool nextCard;
};

#endif
  
