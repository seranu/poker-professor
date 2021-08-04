#pragma once
#include "types.hpp"
#include <deck.hpp>
#include <optional>

namespace professor
{
class Board
{
public:
    Board(Deck deck)
        : mDeck(deck)
    {}

    void reset();
    void drawFlop();
    void drawTurn();
    void drawRiver();

private:
    Deck mDeck;
    std::optional<std::array<Card, 3>> mFlop;
    std::optional<Card> mTurn;
    std::optional<Card> mRiver;
};
}