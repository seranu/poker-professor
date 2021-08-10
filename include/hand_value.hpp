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
    virtual ~IHandValueType() {}
    virtual std::string toString() const = 0;
    virtual bool operator< (const struct IHandValueType& other) const = 0;
    virtual bool operator==(const struct IHandValueType& other) const = 0;
    bool operator!=(const struct IHandValueType& other) const
        { return !(*this == other); }

    bool operator>(const struct IHandValueType& other) const
        { return !(*this < other); }
};

struct HighCard: public IHandValueType
{
    CardRanks mCards;

    HighCard(CardRanks ranks)
        : mCards(ranks)
        {
        }

    bool operator==(const struct IHandValueType &other) const override;
    bool operator==(const struct HighCard& other) const;
    bool operator<(const struct IHandValueType& other) const override;
    bool operator<(const struct HighCard& other) const;
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

    bool operator==(const struct IHandValueType &other) const override;
    bool operator==(const struct OnePair &other) const;
    bool operator<(const struct IHandValueType& other) const override;
    bool operator<(const struct OnePair& other) const;

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

    bool operator==(const struct IHandValueType &other) const override;
    bool operator==(const struct TwoPair &other) const;
    bool operator<(const struct IHandValueType& other) const override;
    bool operator<(const struct TwoPair& other) const;

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

    bool operator==(const struct IHandValueType &other) const override;
    bool operator==(const struct Tripps &other) const;
    bool operator<(const struct IHandValueType& other) const override;
    bool operator<(const struct Tripps &other) const;

    std::string toString() const override;
};

struct Straight: public IHandValueType
{
    CardRank mHighCard;

    explicit Straight(CardRank highCard)
        : mHighCard(highCard)
        {
        }

    bool operator==(const struct IHandValueType &other) const override;
    bool operator==(const struct Straight &other) const;
    bool operator<(const struct IHandValueType& other) const override;
    bool operator<(const struct Straight &other) const;

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

    bool operator==(const struct IHandValueType &other) const override;
    bool operator==(const struct Flush &other) const;
    bool operator<(const struct IHandValueType& other) const override;
    bool operator<(const struct Flush &other) const;

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

    bool operator==(const struct IHandValueType &other) const override;
    bool operator==(const struct FullHouse& other) const;
    bool operator<(const struct IHandValueType& other) const override;
    bool operator<(const struct FullHouse &other) const;

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

    bool operator==(const struct IHandValueType &other) const override;
    bool operator==(const struct Quads &other) const;
    bool operator<(const struct IHandValueType& other) const override;
    bool operator<(const struct Quads &other) const;

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

    bool operator==(const struct IHandValueType &other) const override;
    bool operator==(const struct StraightFlush &other) const;
    bool operator<(const struct IHandValueType& other) const override;
    bool operator<(const struct StraightFlush &other) const;

    std::string toString() const override;
};

struct RoyalFlush: public IHandValueType
{
    Suit mSuit;

    explicit RoyalFlush(Suit suit)
        : mSuit(suit)
        {
        }

    bool operator==(const struct IHandValueType &other) const override;
    bool operator==(const struct RoyalFlush &other) const;
    bool operator<(const struct IHandValueType& other) const override;
    bool operator<(const struct RoyalFlush &other) const;

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


std::map<uint64_t, Suit, std::greater<uint64_t>> &getRoyalFlushesMap();
std::map<uint64_t, Suit, std::greater<uint64_t>> &getStraightFlushesMap();


class HandValue
{
public:
    HandValue(const Cards &cards);

    IHandValueType& getHandValueType() const;

    static std::unique_ptr<IHandValueType> evaluateHand(const Cards& cards);
private:
    std::unique_ptr<IHandValueType> mHandValueType;
};

}
