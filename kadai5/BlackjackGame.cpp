#include "BlackjackGame.h"

BlackjackGame::BlackjackGame() = default;

void BlackjackGame::StartGame() {
    srand(static_cast<unsigned>(time(0)));

    m_DeckSize = 52;
    InitializeDeck();

    m_Player.AddCard(DealCard());
    m_Dealer.AddCard(DealCard());
    m_Player.AddCard(DealCard());

    DisplayGameState();

    while (!m_Player.IsBusted() && (m_Player.GetScore() < 21) && (PlayerDecision() == 'h')) {
        m_Player.AddCard(DealCard());
        DisplayGameState();
    }

    while (m_Dealer.GetScore() < 17) {
        m_Dealer.AddCard(DealCard());
    }

    DisplayFinalResult();
}
