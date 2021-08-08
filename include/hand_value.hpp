#pragma once

#include "card.hpp"

#include <optional>
#include <string>
#include <map>
#include <unordered_map>
#include <variant>
#include <memory>
#include <cassert>

namespace professor
{
struct IHandValueType
{
    virtual std::string toString() const = 0;
    virtual bool lessThan(const struct IHandValueType& other) {
        assert(false); // should not happen;
    }
    virtual bool lessThan(const struct HighCard& other) const = 0;
    virtual bool lessThan(const struct OnePair& other) const = 0;
    virtual bool lessThan(const struct TwoPair& other) const = 0;
    virtual bool lessThan(const struct Tripps& other) const = 0;
    virtual bool lessThan(const struct Straight& other) const = 0;
    virtual bool lessThan(const struct Flush& other) const = 0;
    virtual bool lessThan(const struct FullHouse& other) const = 0;
    virtual bool lessThan(const struct Quads& other) const = 0;
    virtual bool lessThan(const struct StraightFlush& other) const = 0;
    virtual bool lessThan(const struct RoyalFlush& other) const = 0;
};

struct HighCard: public IHandValueType
{
    CardRanks mCards;

    HighCard(CardRanks ranks)
        : mCards(ranks)
        {
        }

    bool operator==(const struct HighCard& other) const;

    bool lessThan(const struct HighCard& other) const override;
    bool lessThan(const struct OnePair& other) const override;
    bool lessThan(const struct TwoPair& other) const override;
    bool lessThan(const struct Tripps& other) const override;
    bool lessThan(const struct Straight& other) const override;
    bool lessThan(const struct Flush& other) const override;
    bool lessThan(const struct FullHouse& other) const override;
    bool lessThan(const struct Quads& other) const override;
    bool lessThan(const struct StraightFlush& other) const override;
    bool lessThan(const struct RoyalFlush& other) const override;

    std::string toString() const override;
};

struct OnePair: public IHandValueType
{
    CardRank mPair;
    CardRanks mKickers;

    OnePair(CardRank pair, CardRanks kickers)
        : mPair(pair)
        , mKickers(kickers)
        {
        }
    bool operator==(const struct OnePair &other) const;

    bool lessThan(const struct HighCard& other) const override;
    bool lessThan(const struct OnePair& other) const override;
    bool lessThan(const struct TwoPair& other) const override;
    bool lessThan(const struct Tripps& other) const override;
    bool lessThan(const struct Straight& other) const override;
    bool lessThan(const struct Flush& other) const override;
    bool lessThan(const struct FullHouse& other) const override;
    bool lessThan(const struct Quads& other) const override;
    bool lessThan(const struct StraightFlush& other) const override;
    bool lessThan(const struct RoyalFlush& other) const override;

    std::string toString() const override;
};

struct TwoPair: public IHandValueType
{
    CardRank mTopPair;
    CardRank mBottomPair;
    CardRank mKicker;

    TwoPair(CardRank topPair, CardRank bottomPair, CardRank kicker)
        : mTopPair(topPair)
        , mBottomPair(bottomPair)
        , mKicker(kicker)
        {
        }

    bool operator==(const struct TwoPair &other) const;

    bool lessThan(const struct HighCard& other) const override;
    bool lessThan(const struct OnePair& other) const override;
    bool lessThan(const struct TwoPair& other) const override;
    bool lessThan(const struct Tripps& other) const override;
    bool lessThan(const struct Straight& other) const override;
    bool lessThan(const struct Flush& other) const override;
    bool lessThan(const struct FullHouse& other) const override;
    bool lessThan(const struct Quads& other) const override;
    bool lessThan(const struct StraightFlush& other) const override;
    bool lessThan(const struct RoyalFlush& other) const override;

    std::string toString() const override;
};

struct Tripps: public IHandValueType
{
    CardRank mTripps;
    CardRanks mKickers;

    Tripps(CardRank tripps, CardRanks kickers)
        : mTripps(tripps)
        , mKickers(kickers)
        {
        }

    bool operator==(const struct Tripps &other) const;

    bool lessThan(const struct HighCard& other) const override;
    bool lessThan(const struct OnePair& other) const override;
    bool lessThan(const struct TwoPair& other) const override;
    bool lessThan(const struct Tripps& other) const override;
    bool lessThan(const struct Straight& other) const override;
    bool lessThan(const struct Flush& other) const override;
    bool lessThan(const struct FullHouse& other) const override;
    bool lessThan(const struct Quads& other) const override;
    bool lessThan(const struct StraightFlush& other) const override;
    bool lessThan(const struct RoyalFlush& other) const override;

    std::string toString() const override;
};

struct Straight: public IHandValueType
{
    CardRank mHighCard;

    explicit Straight(CardRank highCard)
        : mHighCard(highCard)
        {
        }

    bool operator==(const struct Straight &other) const;

    bool lessThan(const struct HighCard& other) const override;
    bool lessThan(const struct OnePair& other) const override;
    bool lessThan(const struct TwoPair& other) const override;
    bool lessThan(const struct Tripps& other) const override;
    bool lessThan(const struct Straight& other) const override;
    bool lessThan(const struct Flush& other) const override;
    bool lessThan(const struct FullHouse& other) const override;
    bool lessThan(const struct Quads& other) const override;
    bool lessThan(const struct StraightFlush& other) const override;
    bool lessThan(const struct RoyalFlush& other) const override;

    std::string toString() const override;
};

struct Flush: public IHandValueType
{
    CardRanks mCards;
    Suit mSuit;

    Flush(CardRanks cards, Suit suit)
        : mCards(cards)
        , mSuit(suit)
        {
        }

    bool operator==(const struct Flush &other) const;
    bool lessThan(const struct HighCard& other) const override;
    bool lessThan(const struct OnePair& other) const override;
    bool lessThan(const struct TwoPair& other) const override;
    bool lessThan(const struct Tripps& other) const override;
    bool lessThan(const struct Straight& other) const override;
    bool lessThan(const struct Flush& other) const override;
    bool lessThan(const struct FullHouse& other) const override;
    bool lessThan(const struct Quads& other) const override;
    bool lessThan(const struct StraightFlush& other) const override;
    bool lessThan(const struct RoyalFlush& other) const override;

    std::string toString() const override;
};

struct FullHouse: public IHandValueType
{
    CardRank mTripps;
    CardRank mPair;

    FullHouse(CardRank tripps, CardRank pair)
        : mTripps(tripps)
        , mPair(pair)
        {
        }

    bool operator==(const struct FullHouse& other) const;
    bool lessThan(const struct HighCard& other) const override;
    bool lessThan(const struct OnePair& other) const override;
    bool lessThan(const struct TwoPair& other) const override;
    bool lessThan(const struct Tripps& other) const override;
    bool lessThan(const struct Straight& other) const override;
    bool lessThan(const struct Flush& other) const override;
    bool lessThan(const struct FullHouse& other) const override;
    bool lessThan(const struct Quads& other) const override;
    bool lessThan(const struct StraightFlush& other) const override;
    bool lessThan(const struct RoyalFlush& other) const override;

    std::string toString() const override;
};

struct Quads: public IHandValueType
{
    CardRank mQuads;
    CardRank mKicker;

    Quads(CardRank quads, CardRank kicker)
        : mQuads(quads)
        , mKicker(kicker)
        {
        }

    bool operator==(const struct Quads &other) const;
    bool lessThan(const struct HighCard& other) const override;
    bool lessThan(const struct OnePair& other) const override;
    bool lessThan(const struct TwoPair& other) const override;
    bool lessThan(const struct Tripps& other) const override;
    bool lessThan(const struct Straight& other) const override;
    bool lessThan(const struct Flush& other) const override;
    bool lessThan(const struct FullHouse& other) const override;
    bool lessThan(const struct Quads& other) const override;
    bool lessThan(const struct StraightFlush& other) const override;
    bool lessThan(const struct RoyalFlush& other) const override;

    std::string toString() const override;
};

struct StraightFlush: public IHandValueType
{
    CardRank mHighCard;
    Suit mSuit;

    StraightFlush(CardRank highCard, Suit suit)
        : mHighCard(highCard)
        , mSuit(suit)
        {
        }

    bool operator==(const struct StraightFlush &other) const;
    bool lessThan(const struct HighCard& other) const override;
    bool lessThan(const struct OnePair& other) const override;
    bool lessThan(const struct TwoPair& other) const override;
    bool lessThan(const struct Tripps& other) const override;
    bool lessThan(const struct Straight& other) const override;
    bool lessThan(const struct Flush& other) const override;
    bool lessThan(const struct FullHouse& other) const override;
    bool lessThan(const struct Quads& other) const override;
    bool lessThan(const struct StraightFlush& other) const override;
    bool lessThan(const struct RoyalFlush& other) const override;

    std::string toString() const override;
};

struct RoyalFlush: public IHandValueType
{
    Suit mSuit;

    explicit RoyalFlush(Suit suit)
        : mSuit(suit)
        {
        }

    bool operator==(const struct RoyalFlush &other) const;
    bool lessThan(const struct HighCard& other) const override;
    bool lessThan(const struct OnePair& other) const override;
    bool lessThan(const struct TwoPair& other) const override;
    bool lessThan(const struct Tripps& other) const override;
    bool lessThan(const struct Straight& other) const override;
    bool lessThan(const struct Flush& other) const override;
    bool lessThan(const struct FullHouse& other) const override;
    bool lessThan(const struct Quads& other) const override;
    bool lessThan(const struct StraightFlush& other) const override;
    bool lessThan(const struct RoyalFlush& other) const override;

    std::string toString() const override;
};

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


class HandValue
{
public:
    HandValue(const Cards &cards);

    IHandValueType& getHandValueType() const;

private:
    std::unique_ptr<IHandValueType> mHandValueType;
};

}