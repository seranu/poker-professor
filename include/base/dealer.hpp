#pragma once
#include "board.hpp"
#include "deck.hpp"
#include "player.hpp"
#include <vector>

namespace professor {
class Dealer {
public:
    Dealer(const std::vector<Player>& players);

    void dealPlayerCards();
    void dealFlop();
    void dealTurn();
    void dealRiver();

    // TODO handle side pot
    std::vector<double> evaluate();

    std::vector<double> doOneRound();

private:
    std::vector<Player> mPlayers;
    Deck mDeck;
    Board mBoard;
};
}
