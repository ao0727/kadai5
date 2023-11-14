#pragma once
#ifndef BLACKJACKGAME_H
#define BLACKJACKGAME_H

#include "Player.h"

class BlackjackGame {
public:
    BlackjackGame();

    void StartGame();

private:
    int m_DeckSize;
    Card m_Deck[52];
    Player m_Player;
    Player m_Dealer;

    void InitializeDeck();

    void ShuffleDeck();

    Card DealCard();

    void DisplayGameState();

    char PlayerDecision();

    void DisplayFinalResult();
};

#endif // BLACKJACKGAME_H
