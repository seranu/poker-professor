#pragma once
#include "card.hpp"

namespace professor
{
struct HighCard
{
    Cards cards;
};

struct OnePair
{
    CardRank pairRank;
    Cards cards;
};

struct TwoPair
{
    CardRank topPair;
    CardRank bottomPair;
    CardRank kicker;
};

struct Tripps
{
    CardRank tripps;
    Cards kickers;
};

struct Straight
{
    CardRank highCard;
};

struct Flush
{
    Cards cards;
    Suit suit;
};

struct FullHouse
{
    CardRank tripps;
    CardRank pair;
};

struct StraightFlush
{
    CardRank highCard;
    Suit suit;
};

struct RoyalFlush
{
    Suit suit;
};

typedef std::variant<HighCard, OnePair, TwoPair, Tripps, Straight, Flush, FullHouse, StraightFlush, RoyalFlush> HandValueType;

std::optional<HighCard> getHighCard(const Cards &cards);
std::optional<OnePair> getOnePair(const Cards &cards);
std::optional<TwoPair> getTwoPair(const Cards &cards);
std::optional<Tripps> getTripps(const Cards &cards);
std::optional<Straight> getStraight(const Cards &cards);
std::optional<Flush> getFlush(const Cards &cards);
std::optional<FullHouse> getFullHouse(const Cards &cards);
std::optional<Quads> getQuads(const Cards &cards);
std::optional<StraightFlush> getStraightFlush(const Cards &cards);
std::optional<RoyalFlush> getRoyalFlush(const Cards &cards);

class HandValue
{
public:
    HandValue(const Cards &cards);

    HandValueType getHandValueType() const;

private:
    HandValueType mHandValueType;
};

class PokerResult
{

};

class PokerSolver
{
public:
    PokerResult solve();
};
}
