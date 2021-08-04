#pragma once
#include "card.hpp"
#include "random.hpp"

#include <array>

namespace professor {
class Deck
{
public:
    static constexpr const int kNumCards = 52;

    Deck();
    Deck(const Deck &) = default;
    Deck& operator=(const Deck&) = default;
    Deck(Deck &&) = default;
    Deck& operator=(Deck &&) = default;

    void reset();
    void shuffle();
    Card draw();
private:
    std::array<Card, kNumCards> mCards;
    unsigned short mBurnIdx { 0 };
    std::shared_ptr<Random> mRandom;
};
}