#include "deck.hpp"
#include "random.hpp"
#include <algorithm>

using namespace professor;
namespace {
std::vector<Card> getDefaultDeck()
{
    int i = 0;
    std::vector<Card> result(kNumCards);
    const auto& allRanks = getAllCardRanks();
    const auto& allSuits = getAllSuits();
    for (const auto& suit : allSuits) {
        for (const auto& rank : allRanks) {
            result[i++] = Card(rank, suit);
        }
    }
    return result;
}
static std::vector<Card> sDefaultDeck = getDefaultDeck();
}
namespace professor {

Deck::Deck()
    : mCards(getDefaultDeck())
    , mRandom(Random::get())
{
    reset();
}

Deck::Deck(const std::vector<Card>& cards)
    : mCards(cards)
    , mRandom(Random::get())
{
    reset();
}

void Deck::reset()
{
    mBurnIdx = 0;
    shuffle();
}

void Deck::shuffle()
{
    mRandom->shuffle<>(mCards);
}

Card Deck::draw()
{
    auto drawIdx = mRandom->number(mBurnIdx, mCards.size() - 1);
    return burnCard(drawIdx);
}

Card Deck::burnCard(size_t idx)
{
    std::swap(mCards[mBurnIdx], mCards[idx]);
    mBurnIdx++;
    return mCards[mBurnIdx - 1];
}

void Deck::burnCard(Card card)
{
    for (decltype(mCards.size()) i = 0; i < mCards.size(); i++) {
        if (mCards[i] == card) {
            burnCard(i);
            break;
        }
    }
}

void Deck::burnCards(Cards cards)
{
    auto internalRep = cards.internalRepresentation();
    int leadingZeros = 0;
    while ((leadingZeros = __builtin_clz(internalRep)) < 64) {
        uint64_t card = 1 << (64 - leadingZeros);
        internalRep = internalRep ^ card;
        burnCard(Card(card));
    }
}
}
