#pragma once
#ifndef CARD_H
#define CARD_H

#include <iostream>
#include <sstream>

class Card {
public:
    enum Rank { ACE = 1, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING };
    enum Suit { CLUBS, DIAMONDS, HEARTS, SPADES };

    Card(Rank rank, Suit suit);

    int GetValue() const;

    void DisplayCard() const;

private:
    Rank m_Rank;
    Suit m_Suit;
};

#endif // CARD_H
