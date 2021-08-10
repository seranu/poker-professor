#include "hand_value.hpp"
#include "exception.hpp"

#include <cassert>
#include <set>
#include <sstream>

namespace {
using namespace professor;

std::unordered_map<size_t, int> sTypeInfos = {
    { typeid(HighCard).hash_code(), 0 },
    { typeid(OnePair).hash_code(), 1 },
    { typeid(TwoPair).hash_code(), 2 },
    { typeid(Tripps).hash_code(), 3 },
    { typeid(Straight).hash_code(), 4 },
    { typeid(Flush).hash_code(), 5 },
    { typeid(FullHouse).hash_code(), 6 },
    { typeid(Quads).hash_code(), 7 },
    { typeid(StraightFlush).hash_code(), 8 },
    { typeid(RoyalFlush).hash_code(), 9 }
};

uint16_t aceHighStraight()
{
    return static_cast<uint16_t>(CardRank::Ace) | static_cast<uint16_t>(CardRank::King) | static_cast<uint16_t>(CardRank::Queen) | static_cast<uint16_t>(CardRank::Jack) | static_cast<uint16_t>(CardRank::Ten);
}

uint16_t wheelStraight()
{
    return static_cast<uint16_t>(CardRank::Ace) | static_cast<uint16_t>(CardRank::Two) | static_cast<uint16_t>(CardRank::Three) | static_cast<uint16_t>(CardRank::Four) | static_cast<uint16_t>(CardRank::Five);
}

uint16_t andSuits(const Cards& cards)
{
    auto spades = cards.getSuit(Suit::Spade);
    auto hearts = cards.getSuit(Suit::Heart);
    auto clubs = cards.getSuit(Suit::Clubs);
    auto diamonds = cards.getSuit(Suit::Diamond);

    return spades & hearts & clubs & diamonds;
}

uint16_t orSuits(const Cards& cards)
{
    auto spades = cards.getSuit(Suit::Spade);
    auto hearts = cards.getSuit(Suit::Heart);
    auto clubs = cards.getSuit(Suit::Clubs);
    auto diamonds = cards.getSuit(Suit::Diamond);

    return spades | hearts | clubs | diamonds;
}

uint16_t xorSuits(const Cards& cards)
{
    auto spades = cards.getSuit(Suit::Spade);
    auto hearts = cards.getSuit(Suit::Heart);
    auto clubs = cards.getSuit(Suit::Clubs);
    auto diamonds = cards.getSuit(Suit::Diamond);

    return spades ^ hearts ^ clubs ^ diamonds;
}

CardRank highCard(uint64_t cards)
{
    auto leadingZeros = __builtin_clzll(cards) % 16;
    return static_cast<CardRank>(1 << (15 - leadingZeros));
}

uint16_t firstSetBit(uint16_t number)
{
    auto leadingZeros = __builtin_clz(number) - 16;
    return 1 << (15 - leadingZeros);
}
CardRank highCard(uint16_t cards)
{
    return static_cast<CardRank>(firstSetBit(cards));
}

uint16_t getSameCards(const Cards& cards)
{
    auto spades = cards.getSuit(Suit::Spade);
    auto hearts = cards.getSuit(Suit::Heart);
    auto clubs = cards.getSuit(Suit::Clubs);
    auto diamonds = cards.getSuit(Suit::Diamond);

    return (spades & hearts) | (spades & clubs) | (spades & diamonds)
        | (hearts & clubs) | (hearts & diamonds) | (clubs & diamonds);
}
std::map<uint64_t, Suit, std::greater<uint64_t>> generateRoyalFlushesMap()
{
    decltype(generateRoyalFlushesMap()) result;
    for (auto suit : getAllSuits()) {
        uint64_t cards = static_cast<uint64_t>(aceHighStraight()) << static_cast<unsigned short>(suit);
        result[cards] = suit;
    }
    return result;
}

std::map<uint64_t, Suit, std::greater<uint64_t>> generateStraightFlushesMap()
{
    decltype(generateStraightFlushesMap()) result;
    for (auto suit : getAllSuits()) {
        uint16_t cardRanks = aceHighStraight();
        // Exclude royal flush.
        cardRanks = cardRanks >> 1;
        while (__builtin_popcount(cardRanks) == 5) {
            uint64_t cards = static_cast<uint64_t>(cardRanks) << static_cast<unsigned short>(suit);
            result[cards] = suit;
            cardRanks >>= 1;
        }

        // Add wheel straight;
        uint64_t suitedWheelStraight = static_cast<uint64_t>(wheelStraight()) << static_cast<unsigned short>(suit);
        result[suitedWheelStraight] = suit;
    }
    return result;
}

std::set<uint16_t, std::greater<uint64_t>> generateStraightMap()
{
    decltype(generateStraightMap()) result;
    uint16_t cardRanks = aceHighStraight();
    while (__builtin_popcount(cardRanks) == 5) {
        result.insert(cardRanks);
        cardRanks >>= 1;
    }
    result.insert(wheelStraight());
    return result;
}
}

namespace professor {

std::map<uint64_t, Suit, std::greater<uint64_t>>& getRoyalFlushesMap()
{
    static std::map<uint64_t, Suit, std::greater<uint64_t>> sRoyalFlushes = generateRoyalFlushesMap();
    return sRoyalFlushes;
}

std::map<uint64_t, Suit, std::greater<uint64_t>>& getStraightFlushesMap()
{
    static std::map<uint64_t, Suit, std::greater<uint64_t>> sStraightFlushes = generateStraightFlushesMap();
    return sStraightFlushes;
}

std::set<uint16_t, std::greater<uint64_t>>& getStraightMap()
{
    static std::set<uint16_t, std::greater<uint64_t>> sStraights = generateStraightMap();
    return sStraights;
}

uint16_t getFirstNSetBits(uint16_t number, unsigned short count)
{
    assert(count < sizeof(number) * 8);
    uint16_t result = 0;
    for (decltype(count) i = 0; i < count; i++) {
        auto nextBit = firstSetBit(number);
        assert(nextBit);
        result |= nextBit;
        number ^= nextBit;
    }
    return result;
}

std::optional<HighCard> getHighCard(const Cards& cards)
{
    auto distinctCards = orSuits(cards);
    return { HighCard { getFirstNSetBits(distinctCards, 5) } };
}

std::optional<OnePair> getOnePair(const Cards& cards)
{
    auto sameCards = getSameCards(cards);
    if (__builtin_popcount(sameCards) != 1) {
        return {};
    }

    auto kickers = getFirstNSetBits(orSuits(cards) ^ sameCards, 3);
    return { OnePair { static_cast<CardRank>(sameCards), kickers } };
}

std::optional<TwoPair> getTwoPair(const Cards& cards)
{
    auto sameCards = getSameCards(cards);
    if (__builtin_popcount(sameCards) < 2) {
        return {};
    }
    auto firstPair = highCard(sameCards);
    auto secondPair = highCard(static_cast<uint16_t>(~static_cast<uint16_t>(firstPair) & sameCards));
    auto ranks = orSuits(cards);
    auto kicker = highCard(static_cast<uint16_t>(~(static_cast<uint16_t>(firstPair) | static_cast<uint16_t>(secondPair)) & ranks));
    return { TwoPair { firstPair, secondPair, kicker } };
}

std::optional<Tripps> getTripps(const Cards& cards)
{
    auto sameCards = getSameCards(cards);
    auto distinctCards = orSuits(cards);
    auto potentialTripps = static_cast<uint16_t>(sameCards & xorSuits(cards));
    if (potentialTripps == 0) {
        return {};
    }

    auto kickers = getFirstNSetBits(potentialTripps ^ distinctCards, 2);
    return { Tripps { highCard(potentialTripps), CardRanks(kickers) } };
}

std::optional<Straight> getStraight(const Cards& cards)
{
    const auto orCards = orSuits(cards);
    uint16_t straight = aceHighStraight();
    const auto& wStraight = wheelStraight();
    while (__builtin_popcount(straight) == 5) {
        if ((orCards & straight) == straight) {
            return { Straight { highCard(straight) } };
        }
        straight >>= 1;
    }

    if ((orCards & wStraight) == wStraight) {
        return { Straight { CardRank::Five } };
    }
    return {};
}

#define CHECK_RETURN_FLUSH(cards, suit)                                           \
    {                                                                             \
        const auto& suitCards = cards.getSuit(suit);                              \
        if (__builtin_popcount(suitCards) >= 5) {                                 \
            return { Flush { CardRanks(getFirstNSetBits(suitCards, 5)), suit } }; \
        }                                                                         \
    }

std::optional<Flush> getFlush(const Cards& cards)
{
    CHECK_RETURN_FLUSH(cards, Suit::Spade);
    CHECK_RETURN_FLUSH(cards, Suit::Diamond);
    CHECK_RETURN_FLUSH(cards, Suit::Clubs);
    CHECK_RETURN_FLUSH(cards, Suit::Heart);
    return {};
}

std::optional<FullHouse> getFullHouse(const Cards& cards)
{
    auto sameCards = getSameCards(cards);
    if (__builtin_popcount(sameCards) < 2) {
        return {};
    }

    auto potentialTripps = static_cast<uint16_t>(sameCards & xorSuits(cards));
    if (potentialTripps == 0) {
        return {};
    }

    auto numTripps = __builtin_popcount(potentialTripps);
    if (numTripps == 1) {
        auto potentialPairs = static_cast<uint16_t>(sameCards ^ potentialTripps);
        if (potentialPairs == 0) {
            return {};
        }

        auto highestPair = highCard(potentialPairs);
        return { FullHouse { static_cast<CardRank>(potentialTripps), static_cast<CardRank>(highestPair) } };
    }

    if (numTripps == 2) {
        auto topTripps = highCard(potentialTripps);
        return { FullHouse { topTripps, static_cast<CardRank>(potentialTripps ^ static_cast<uint16_t>(topTripps)) } };
    }

    throw Exception("Logic error");
}

std::optional<Quads> getQuads(const Cards& cards)
{

    uint16_t potentialQuad = andSuits(cards);
    if (potentialQuad) {
        return { Quads { static_cast<CardRank>(potentialQuad), highCard(xorSuits(cards)) } };
    }
    return {};
}

#define CHECK_RETURN_STRAIGHT_FLUSH(cards, suit)                       \
    {                                                                  \
        const auto suitCards = cards.getSuit(suit);                    \
        uint16_t straight = aceHighStraight() >> 1;                    \
        while (__builtin_popcount(straight) == 5) {                    \
            if ((suitCards & straight) == straight) {                  \
                return { StraightFlush { highCard(straight), suit } }; \
            }                                                          \
            straight >>= 1;                                            \
        }                                                              \
        if ((suitCards & wStraight) == wStraight) {                    \
            return { StraightFlush { CardRank::Five, suit } };         \
        }                                                              \
    }
std::optional<StraightFlush> getStraightFlush(const Cards& cards)
{
    const auto& wStraight = wheelStraight();
    CHECK_RETURN_STRAIGHT_FLUSH(cards, Suit::Spade);
    CHECK_RETURN_STRAIGHT_FLUSH(cards, Suit::Diamond);
    CHECK_RETURN_STRAIGHT_FLUSH(cards, Suit::Heart);
    CHECK_RETURN_STRAIGHT_FLUSH(cards, Suit::Clubs);
    return {};
}

#define CHECK_RETURN_ROYAL_FLUSH(suit)                                                                       \
    {                                                                                                        \
        const auto& suitRoyalFlush = static_cast<uint64_t>(royalFlush) << static_cast<unsigned short>(suit); \
        if ((cardsInt & suitRoyalFlush) == suitRoyalFlush) {                                                 \
            return { RoyalFlush { suit } };                                                                  \
        }                                                                                                    \
    }

std::optional<RoyalFlush> getRoyalFlush(const Cards& cards)
{
    const uint16_t royalFlush = aceHighStraight();
    const uint64_t cardsInt = cards.internalRepresentation();
    CHECK_RETURN_ROYAL_FLUSH(Suit::Spade);
    CHECK_RETURN_ROYAL_FLUSH(Suit::Diamond);
    CHECK_RETURN_ROYAL_FLUSH(Suit::Clubs);
    CHECK_RETURN_ROYAL_FLUSH(Suit::Heart);
    return {};
}

//// HighCard //////////////////////////////////////////////////////////////////

bool HighCard::operator<(const struct IHandValueType& other) const
{
    const auto& thisTypeInfo = typeid(*this);
    const auto& otherTypeInfo = typeid(other);
    if (thisTypeInfo == otherTypeInfo) {
        auto otherDerrived = static_cast<const HighCard&>(other);
        return *this < otherDerrived;
    }

    return sTypeInfos[thisTypeInfo.hash_code()] < sTypeInfos[otherTypeInfo.hash_code()];
}

bool HighCard::operator<(const struct HighCard& other) const
{
    return mCards < other.mCards;
}

bool HighCard::operator==(const struct IHandValueType& other) const
{
    if (typeid(other) == typeid(*this)) {
        auto otherDerrived = static_cast<const HighCard&>(other);
        return *this == otherDerrived;
    }
    return false;
}

bool HighCard::operator==(const struct HighCard& other) const
{
    return mCards == other.mCards;
}

std::string HighCard::toString() const
{
    std::ostringstream oss;
    oss << "High card: " << mCards.toString();
    return oss.str();
}

//// OnePair ///////////////////////////////////////////////////////////////////

bool OnePair::operator==(const struct OnePair& other) const
{
    return mPair == other.mPair && mKickers == other.mKickers;
}

std::string OnePair::toString() const
{
    std::ostringstream oss;
    oss << "One pair of " << toStyleString(mPair) << "s with kickers : [" << mKickers.toString() << "]";
    return oss.str();
}

bool OnePair::operator<(const struct IHandValueType& other) const
{
    const auto& thisTypeInfo = typeid(*this);
    const auto& otherTypeInfo = typeid(other);
    if (thisTypeInfo == otherTypeInfo) {
        auto otherDerrived = static_cast<const OnePair&>(other);
        return *this < otherDerrived;
    }

    return sTypeInfos[thisTypeInfo.hash_code()] < sTypeInfos[otherTypeInfo.hash_code()];
}

bool OnePair::operator<(const struct OnePair& other) const
{
    if (mPair == other.mPair) {
        return mKickers < other.mKickers;
    }
    return mPair < other.mPair;
}

bool OnePair::operator==(const struct IHandValueType& other) const
{
    if (typeid(other) == typeid(*this)) {
        auto otherDerrived = static_cast<const OnePair&>(other);
        return *this == otherDerrived;
    }
    return false;
}

//// TwoPair ///////////////////////////////////////////////////////////////////

bool TwoPair::operator==(const struct IHandValueType& other) const
{
    if (typeid(other) == typeid(*this)) {
        auto otherDerrived = static_cast<const TwoPair&>(other);
        return *this == otherDerrived;
    }
    return false;
}

bool TwoPair::operator==(const struct TwoPair& other) const
{
    return mTopPair == other.mTopPair && mBottomPair == other.mBottomPair && mKicker == other.mKicker;
}

std::string TwoPair::toString() const
{
    std::ostringstream oss;
    oss << "Two pair: " << toStyleString(mTopPair) << "s with " << toStyleString(mBottomPair) << "s, " << toStyleString(mKicker) << " kicker";
    return oss.str();
}

bool TwoPair::operator<(const struct IHandValueType& other) const
{
    const auto& thisTypeInfo = typeid(*this);
    const auto& otherTypeInfo = typeid(other);
    if (thisTypeInfo == otherTypeInfo) {
        auto otherDerrived = static_cast<const TwoPair&>(other);
        return *this < otherDerrived;
    }

    return sTypeInfos[thisTypeInfo.hash_code()] < sTypeInfos[otherTypeInfo.hash_code()];
}

bool TwoPair::operator<(const struct TwoPair& other) const
{
    if (mTopPair == other.mTopPair) {
        if (mBottomPair == other.mBottomPair) {
            return mKicker < other.mKicker;
        }

        return mBottomPair < other.mBottomPair;
    }
    return mTopPair < other.mTopPair;
}

//// Tripps ///////////////////////////////////////////////////////////////////

bool Tripps::operator==(const struct IHandValueType& other) const
{
    if (typeid(*this) == typeid(other)) {
        auto otherDerrived = static_cast<const Tripps&>(other);
        return *this == otherDerrived;
    }
    return false;
}

bool Tripps::operator==(const struct Tripps& other) const
{
    return mTripps == other.mTripps && mKickers == other.mKickers;
}

std::string Tripps::toString() const
{
    std::ostringstream oss;
    oss << "Three of a kind: " << toStyleString(mTripps) << "s, " << mKickers.toString() << " kickers";
    return oss.str();
}

bool Tripps::operator<(const struct IHandValueType& other) const
{
    const auto& thisTypeInfo = typeid(*this);
    const auto& otherTypeInfo = typeid(other);
    if (thisTypeInfo == otherTypeInfo) {
        auto otherDerrived = static_cast<const Tripps&>(other);
        return *this < otherDerrived;
    }

    return sTypeInfos[thisTypeInfo.hash_code()] < sTypeInfos[otherTypeInfo.hash_code()];
}

bool Tripps::operator<(const struct Tripps& other) const
{
    if (mTripps == other.mTripps) {
        return mKickers < other.mKickers;
    }
    return mTripps < other.mTripps;
}

//// Straight //////////////////////////////////////////////////////////////////

bool Straight::operator==(const struct IHandValueType& other) const
{
    if (typeid(*this) == typeid(other)) {
        auto otherDerrived = static_cast<const Straight&>(other);
        return *this == otherDerrived;
    }
    return false;
}

bool Straight::operator<(const struct IHandValueType& other) const
{
    const auto& thisTypeInfo = typeid(*this);
    const auto& otherTypeInfo = typeid(other);
    if (thisTypeInfo == otherTypeInfo) {
        auto otherDerrived = static_cast<const Straight&>(other);
        return *this < otherDerrived;
    }

    return sTypeInfos[thisTypeInfo.hash_code()] < sTypeInfos[otherTypeInfo.hash_code()];
}

bool Straight::operator==(const struct Straight& other) const
{
    return mHighCard == other.mHighCard;
}

std::string Straight::toString() const
{
    std::ostringstream oss;
    oss << "Straight " << toStyleString(mHighCard) << " high";
    return oss.str();
}

bool Straight::operator<(const struct Straight& other) const
{
    return mHighCard < other.mHighCard;
}

//// Flush ////////////////////////////////////////////////////////////////////

bool Flush::operator==(const struct Flush& other) const
{
    return mCards == other.mCards && mSuit == other.mSuit;
}

std::string Flush::toString() const
{
    std::ostringstream oss;
    oss << "Flush: " << mCards.toString() << " of suit " << toStyleString(mSuit);
    return oss.str();
}

bool Flush::operator==(const struct IHandValueType& other) const
{
    if (typeid(*this) == typeid(other)) {
        auto otherDerrived = static_cast<const Flush&>(other);
        return *this == otherDerrived;
    }
    return false;
}

bool Flush::operator<(const struct IHandValueType& other) const
{
    const auto& thisTypeInfo = typeid(*this);
    const auto& otherTypeInfo = typeid(other);
    if (thisTypeInfo == otherTypeInfo) {
        auto otherDerrived = static_cast<const Flush&>(other);
        return *this < otherDerrived;
    }

    return sTypeInfos[thisTypeInfo.hash_code()] < sTypeInfos[otherTypeInfo.hash_code()];
}

bool Flush::operator<(const struct Flush& other) const
{
    return mCards < other.mCards;
}

//// FullHouse /////////////////////////////////////////////////////////////////

bool FullHouse::operator==(const struct FullHouse& other) const
{
    return mTripps == other.mTripps && mPair == other.mPair;
}

std::string FullHouse::toString() const
{
    std::ostringstream oss;
    oss << "Full house: " << toStyleString(mTripps) << "s full with " << toStyleString(mPair) << "s";
    return oss.str();
}

bool FullHouse::operator==(const struct IHandValueType& other) const
{
    if (typeid(*this) == typeid(other)) {
        auto otherDerrived = static_cast<const FullHouse&>(other);
        return *this == otherDerrived;
    }
    return false;
}

bool FullHouse::operator<(const struct IHandValueType& other) const
{
    const auto& thisTypeInfo = typeid(*this);
    const auto& otherTypeInfo = typeid(other);
    if (thisTypeInfo == otherTypeInfo) {
        auto otherDerrived = static_cast<const FullHouse&>(other);
        return *this < otherDerrived;
    }

    return sTypeInfos[thisTypeInfo.hash_code()] < sTypeInfos[otherTypeInfo.hash_code()];
}

bool FullHouse::operator<(const struct FullHouse& other) const
{
    if (mTripps == other.mTripps) {
        return mPair < other.mPair;
    }
    return mTripps < other.mTripps;
}

//// Quads /////////////////////////////////////////////////////////////////////

bool Quads::operator==(const struct Quads& other) const
{
    return mQuads == other.mQuads && mKicker == other.mKicker;
}

std::string Quads::toString() const
{
    std::ostringstream oss;
    oss << "Four of a kind: " << toStyleString(mQuads) << ", " << toStyleString(mKicker) << " kicker";
    return oss.str();
}

bool Quads::operator==(const struct IHandValueType& other) const
{
    if (typeid(*this) == typeid(other)) {
        auto otherDerrived = static_cast<const Quads&>(other);
        return *this == otherDerrived;
    }
    return false;
}

bool Quads::operator<(const struct IHandValueType& other) const
{
    const auto& thisTypeInfo = typeid(*this);
    const auto& otherTypeInfo = typeid(other);
    if (thisTypeInfo == otherTypeInfo) {
        auto otherDerrived = static_cast<const Quads&>(other);
        return *this < otherDerrived;
    }

    return sTypeInfos[thisTypeInfo.hash_code()] < sTypeInfos[otherTypeInfo.hash_code()];
}

bool Quads::operator<(const struct Quads& other) const
{
    return mQuads < other.mQuads;
}

//// StraightFlush /////////////////////////////////////////////////////////////

bool StraightFlush::operator==(const struct StraightFlush& other) const
{
    return mHighCard == other.mHighCard && mSuit == other.mSuit;
}

std::string StraightFlush::toString() const
{
    std::ostringstream oss;
    oss << "Straight flush " << toStyleString(mHighCard) << " high, " << toStyleString(mSuit);
    return oss.str();
}

bool StraightFlush::operator==(const struct IHandValueType& other) const
{
    if (typeid(*this) == typeid(other)) {
        auto otherDerrived = static_cast<const StraightFlush&>(other);
        return *this == otherDerrived;
    }
    return false;
}

bool StraightFlush::operator<(const struct IHandValueType& other) const
{
    const auto& thisTypeInfo = typeid(*this);
    const auto& otherTypeInfo = typeid(other);
    if (thisTypeInfo == otherTypeInfo) {
        auto otherDerrived = static_cast<const StraightFlush&>(other);
        return *this < otherDerrived;
    }

    return sTypeInfos[thisTypeInfo.hash_code()] < sTypeInfos[otherTypeInfo.hash_code()];
}

bool StraightFlush::operator<(const struct StraightFlush& other) const
{
    return mHighCard < other.mHighCard;
}

//// RoyalFlush ////////////////////////////////////////////////////////////////

bool RoyalFlush::operator==(const struct RoyalFlush& other) const
{
    return mSuit == other.mSuit;
}

std::string RoyalFlush::toString() const
{
    std::ostringstream oss;
    oss << "Royal flush of " << toStyleString(mSuit);
    return oss.str();
}

bool RoyalFlush::operator==(const struct IHandValueType& other) const
{
    if (typeid(*this) == typeid(other)) {
        auto otherDerrived = static_cast<const RoyalFlush&>(other);
        return *this == otherDerrived;
    }
    return false;
}

bool RoyalFlush::operator<(const struct IHandValueType& other) const
{
    const auto& thisTypeInfo = typeid(*this);
    const auto& otherTypeInfo = typeid(other);
    if (thisTypeInfo == otherTypeInfo) {
        auto otherDerrived = static_cast<const RoyalFlush&>(other);
        return *this < otherDerrived;
    }

    return sTypeInfos[thisTypeInfo.hash_code()] < sTypeInfos[otherTypeInfo.hash_code()];
}

bool RoyalFlush::operator<(const struct RoyalFlush& other) const
{
    return false;
}

//// HandValue ////////////////////////////////////////////////////////////////

HandValue::HandValue(const Cards& cards)
{
    mHandValueType = evaluateHand(cards);
}

IHandValueType& HandValue::getHandValueType() const
{
    return *mHandValueType;
}

std::unique_ptr<IHandValueType> HandValue::evaluateHand(const Cards& cards)
{
    auto royalFlush = getRoyalFlush(cards);
    if (royalFlush) {
        return std::make_unique<RoyalFlush>(*royalFlush);
    }

    auto straightFlush = getStraightFlush(cards);
    if (straightFlush) {
        return std::make_unique<StraightFlush>(*straightFlush);
    }

    auto quads = getQuads(cards);
    if (quads) {
        return std::make_unique<Quads>(*quads);
    }

    auto fullHouse = getFullHouse(cards);
    if (fullHouse) {
        return std::make_unique<FullHouse>(*fullHouse);
    }

    auto flush = getFlush(cards);
    if (flush) {
        return std::make_unique<Flush>(*flush);
    }

    auto straight = getStraight(cards);
    if (straight) {
        return std::make_unique<Straight>(*straight);
    }

    auto tripps = getTripps(cards);
    if (tripps) {
        return std::make_unique<Tripps>(*tripps);
    }

    auto twoPair = getTwoPair(cards);
    if (twoPair) {
        return std::make_unique<TwoPair>(*twoPair);
    }

    auto onePair = getOnePair(cards);
    if (onePair) {
        return std::make_unique<OnePair>(*onePair);
    }

    auto highCard = getHighCard(cards);
    if (!highCard) {
        throw Exception("Failed to determine hand value type");
    }
    return std::make_unique<HighCard>(*highCard);
}

}
