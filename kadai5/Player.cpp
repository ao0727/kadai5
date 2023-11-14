#include "Player.h"

void Player::AddCard(const Card& card) {
    if (m_HandSize < MaxHandSize) {
        m_Hand[m_HandSize] = card;
        m_HandSize++;
    }
}

int Player::GetScore() const {
    int score = 0;
    int numAces = 0;

    for (int i = 0; i < m_HandSize; i++) {
        score += m_Hand[i].GetValue();
        if (m_Hand[i].GetValue() == Card::ACE) {
            numAces++;
        }
    }

    while (numAces > 0 && score > 21) {
        for (int i = 0; i < m_HandSize; i++) {
            if (m_Hand[i].GetValue() == Card::ACE) {
                score -= 10;
                numAces--;
            }
        }
    }

    return score;
}

void Player::ShowHand() const {
    for (int i = 0; i < m_HandSize; i++) {
        m_Hand[i].DisplayCard();
    }
}

bool Player::IsBusted() const {
    return GetScore() > 21;
}
