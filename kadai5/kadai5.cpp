#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <sstream> 
using namespace std;

//コンストラクタを参照できない

class Card {
public:
    enum Rank { ACE = 1, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING };
    enum Suit { CLUBS, DIAMONDS, HEARTS, SPADES };

    Card(Rank rank, Suit suit) : m_Rank(rank), m_Suit(suit) {}

    int GetValue() const {
        if (m_Rank > 10) {
            return 10;
        }
        else if (m_Rank == ACE) {
            return 11;  
        }
        else {
            return m_Rank;
        }
    }

    void DisplayCard() const {
        string rankStr;
        string suitStr;
        stringstream ss;

        switch (m_Rank) {
        case ACE: ss << "A"; break;
        case JACK: ss << "J"; break;
        case QUEEN: ss << "Q"; break;
        case KING: ss << "K"; break;
        default: ss << m_Rank; break;
        }

        rankStr = ss.str();

        switch (m_Suit) {
        case CLUBS: suitStr = "Clubs"; break;
        case DIAMONDS: suitStr = "Diamonds"; break;
        case HEARTS: suitStr = "Hearts"; break;
        case SPADES: suitStr = "Spades"; break;
        }

        cout << rankStr << " of " << suitStr << endl;
    }

private:
    Rank m_Rank;
    Suit m_Suit;
};

class Player {
public:
    void AddCard(const Card& card) {
        if (m_HandSize < MaxHandSize) {
            m_Hand[m_HandSize] = card;
            m_HandSize++;
        }
    }

    int GetScore() const {
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

    void ShowHand() const {
        for (int i = 0; i < m_HandSize; i++) {
            m_Hand[i].DisplayCard();
        }
    }

    bool IsBusted() const {
        return GetScore() > 21;
    }

private:
    static const int MaxHandSize = 10; 
    Card m_Hand[MaxHandSize];
    int m_HandSize = 0;
};

class BlackjackGame {
public:

    BlackjackGame() = default;

    void StartGame() {
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

private:
    int m_DeckSize;
    Card m_Deck[52];
    Player m_Player;
    Player m_Dealer;

    void InitializeDeck() {
        int index = 0;
        for (int suit = Card::CLUBS; suit <= Card::SPADES; suit++) {
            for (int rank = Card::ACE; rank <= Card::KING; rank++) {
                m_Deck[index] = Card(static_cast<Card::Rank>(rank), static_cast<Card::Suit>(suit));
                index++;
            }
        }
    }

    void ShuffleDeck() {
        for (int i = m_DeckSize - 1; i > 0; i--) {
            int j = rand() % (i + 1);
            swap(m_Deck[i], m_Deck[j]);
        }
    }

    Card DealCard() {
        if (m_DeckSize > 0) {
            m_DeckSize--;
            return m_Deck[m_DeckSize];
        }
        else {
            // Deck is empty, create a placeholder card
            return Card(Card::ACE, Card::CLUBS);
        }
    }

    void DisplayGameState() {
        cout << "Player:" << endl;
        m_Player.ShowHand();
        cout << "Player Score: " << m_Player.GetScore() << endl << endl;

        cout << "Dealer:" << endl;
        m_Dealer.ShowHand();
        cout << "Dealer Score: " << m_Dealer.GetScore() << endl << endl;
    }

    char PlayerDecision() {
        char choice;
        cout << " 'h' or 's'";
        cin >> choice;
        return choice;
    }

    void DisplayFinalResult() {
        cout << "Results:" << endl;

        cout << "Player:" << endl;
        m_Player.ShowHand();
        cout << "Player Score: " << m_Player.GetScore() << endl << endl;

        cout << "Dealer:" << endl;
        m_Dealer.ShowHand();
        cout << "Dealer Score: " << m_Dealer.GetScore() << endl << endl;

        if (m_Player.IsBusted() || (!m_Player.IsBusted() && m_Dealer.IsBusted()) || (m_Player.GetScore() > m_Dealer.GetScore())) {
            cout << "Player win" << endl;
        }
        else if (m_Dealer.IsBusted() || (m_Player.GetScore() < m_Dealer.GetScore())) {
            cout << "Dealer win" << endl;
        }
        else {
            cout << "tie" << endl;
        }
    }
};

int main() {
    BlackjackGame game;
    game.StartGame();

    
}
