#pragma once
#include "card.hpp"
#include <optional>
#include <variant>
#include <unordered_map>
#include <map>

namespace professor
{
struct HighCard
{
    CardRanks mCards;
    bool operator==(const struct HighCard& other) const;
    std::string toString() const;
};

struct OnePair
{
    CardRank mPair;
    CardRanks mKickers;
    bool operator==(const struct OnePair &other) const;
    std::string toString() const;
};

struct TwoPair
{
    CardRank mTopPair;
    CardRank mBottomPair;
    CardRank mKicker;
    bool operator==(const struct TwoPair &other) const;
    std::string toString() const;
};

struct Tripps
{
    CardRank mTripps;
    CardRanks mKickers;
    bool operator==(const struct Tripps &other) const;
    std::string toString() const;
};

struct Straight
{
    CardRank mHighCard;
    bool operator==(const struct Straight &other) const;
    std::string toString() const;
};

struct Flush
{
    CardRanks mCards;
    Suit mSuit;
    bool operator==(const struct Flush &other) const;
    std::string toString() const;
};

struct FullHouse
{
    CardRank mTripps;
    CardRank mPair;
    bool operator==(const struct FullHouse& other) const;
    std::string toString() const;
};

struct Quads
{
    CardRank mQuads;
    CardRank mKicker;
    bool operator==(const struct Quads &other) const;
    std::string toString() const;
};

struct StraightFlush
{
    CardRank mHighCard;
    Suit mSuit;
    bool operator==(const struct StraightFlush &other) const;
    std::string toString() const;
};

struct RoyalFlush
{
    Suit mSuit;
    bool operator==(const struct RoyalFlush &other) const;
    std::string toString() const;
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


std::unordered_map<uint64_t, Suit> getRoyalFlushesMap();
std::map<uint64_t, Suit> getStraightFlushesMap();

/*
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
*/
class PokerSolver
{
public:
 //   PokerResult solve();
};
}
