#include "deck.hpp"
#include "random.hpp"
#include <algorithm>

using namespace professor;
namespace {
std::array<Card, Deck::kNumCards> getDefaultDeck()
{
    int i = 0;
    std::array<Card, Deck::kNumCards> result;
    for(CardRank rank = CardRank::Two; rank <= CardRank::Ace; rank = static_cast<CardRank>(static_cast<unsigned>(rank) + 1)) {
        for(Suit suit = Suit::Clubs; suit <= Suit::Spade; suit = static_cast<Suit>(static_cast<unsigned>(suit) + 1)) {
            result[i] = Card(rank, suit);
        }
    }
    return result;
}
static std::array<Card, professor::Deck::kNumCards> sDefaultDeck = getDefaultDeck();
}
namespace professor
{

Deck::Deck()
: mRandom(Random::get())
{
    reset();
}

void Deck::reset()
{
    mBurnIdx = 0;
    mCards = getDefaultDeck();
    shuffle();
}

void Deck::shuffle()
{
    mRandom->shuffle<Card, kNumCards>(mCards);
}

Card Deck::draw()
{
    auto drawIdx = mRandom->number(mBurnIdx + 1, kNumCards - 1);
    std::swap(mCards[mBurnIdx], mCards[drawIdx]);
    mBurnIdx++;
}


}