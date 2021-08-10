#pragma once
#include "card.hpp"
#include "deck.hpp"

#include <optional>

namespace professor {
struct Board {
    void reset();
    void drawFlop(Deck& deck);
    void drawTurn(Deck& deck);
    void drawRiver(Deck& deck);
    Cards getBoard() const;

    std::optional<Cards> mFlop;
    std::optional<Card> mTurn;
    std::optional<Card> mRiver;
};
}