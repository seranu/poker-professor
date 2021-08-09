#pragma once
#include "card.hpp"
#include "random.hpp"

#include <array>

namespace professor {
constexpr const int kNumCards = 52;
class Deck
{
public:
    Deck();
    Deck(const std::vector<Card> &cards);
    Deck(const Deck &) = default;
    Deck& operator=(const Deck&) = default;
    Deck(Deck &&) = default;
    Deck& operator=(Deck &&) = default;

    void reset();
    void shuffle();
    void burnCard(Card card);
    void burnCards(Cards cards);
    Card draw();
private:
    Card burnCard(size_t idx);
    std::vector<Card> mCards;
    unsigned short mBurnIdx { 0 };
    std::shared_ptr<Random> mRandom;
};
}