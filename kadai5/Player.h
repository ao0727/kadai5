#ifndef PLAYER_H
#define PLAYER_H

#include "Card.h"

class Player {
public:
    void AddCard(const Card& card);

    int GetScore() const;

    void ShowHand() const;

    bool IsBusted() const;

protected:
    static const int MaxHandSize = 10;
    Card m_Hand[MaxHandSize];
    int m_HandSize = 0;
};

#endif // PLAYER_H
