#include "hand_value.hpp"
#include "exception.hpp"

#include <sstream>
#include <set>
#include <cassert>

namespace
{
using namespace professor;

std::unordered_map<size_t, int> sTypeInfos = {
    { typeid(HighCard).hash_code(),      0 },
    { typeid(OnePair).hash_code(),       1 },
    { typeid(TwoPair).hash_code(),       2 },
    { typeid(Tripps).hash_code(),        3 },
    { typeid(Straight).hash_code(),      4 },
    { typeid(Flush).hash_code(),         5 },
    { typeid(FullHouse).hash_code(),     6 },
    { typeid(Quads).hash_code(),         7 },
    { typeid(StraightFlush).hash_code(), 8 },
    { typeid(RoyalFlush).hash_code(),    9 }
};

uint16_t aceHighStraight()
{
    return static_cast<uint16_t>(CardRank::Ace) | 
           static_cast<uint16_t>(CardRank::King) | 
           static_cast<uint16_t>(CardRank::Queen) | 
           static_cast<uint16_t>(CardRank::Jack) | 
           static_cast<uint16_t>(CardRank::Ten);
}

uint16_t wheelStraight()
{
     return static_cast<uint16_t>(CardRank::Ace) | 
           static_cast<uint16_t>(CardRank::Two) | 
           static_cast<uint16_t>(CardRank::Three) | 
           static_cast<uint16_t>(CardRank::Four) | 
           static_cast<uint16_t>(CardRank::Five);
}

uint16_t andSuits(const Cards& cards)
{
    auto spades = cards.getSuit(Suit::Spade);
    auto hearts = cards.getSuit(Suit::Heart);
    auto clubs  = cards.getSuit(Suit::Clubs);
    auto diamonds = cards.getSuit(Suit::Diamond); 
   
    return spades & hearts & clubs & diamonds;
}

uint16_t orSuits(const Cards& cards)
{
    auto spades = cards.getSuit(Suit::Spade);
    auto hearts = cards.getSuit(Suit::Heart);
    auto clubs  = cards.getSuit(Suit::Clubs);
    auto diamonds = cards.getSuit(Suit::Diamond); 
   
    return spades | hearts | clubs | diamonds;
}

uint16_t xorSuits(const Cards& cards)
{
    auto spades = cards.getSuit(Suit::Spade);
    auto hearts = cards.getSuit(Suit::Heart);
    auto clubs  = cards.getSuit(Suit::Clubs);
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

uint16_t getSameCards(const Cards &cards)
{
    auto spades = cards.getSuit(Suit::Spade);
    auto hearts = cards.getSuit(Suit::Heart);
    auto clubs  = cards.getSuit(Suit::Clubs);
    auto diamonds = cards.getSuit(Suit::Diamond); 

    return (spades & hearts) | (spades & clubs) | (spades & diamonds)
        | (hearts & clubs) | (hearts & diamonds) | (clubs & diamonds);

}
}

namespace professor
{

std::unordered_map<uint64_t, Suit> getRoyalFlushesMap()
{
    decltype(getRoyalFlushesMap()) result;
    for(auto suit: getAllSuits())
    {
        uint64_t cards = static_cast<uint64_t>(aceHighStraight()) << static_cast<unsigned short>(suit);
        result[cards] = suit;
    }
    return result;
}

std::map<uint64_t, Suit> getStraightFlushesMap()
{
    decltype(getStraightFlushesMap()) result;
    for(auto suit: getAllSuits()) 
    {
        uint16_t cardRanks = aceHighStraight(); 
        // Exclude royal flush.
        cardRanks = cardRanks >> 1;
        while(__builtin_popcount(cardRanks) == 5) {
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

std::set<uint16_t> getStraightMap()
{
    decltype(getStraightMap()) result;
    uint16_t cardRanks = aceHighStraight();
    while(__builtin_popcount(cardRanks) == 5) {
        result.insert(cardRanks);
        cardRanks >>= 1;
    }
    result.insert(wheelStraight());
    return result;
}

uint16_t getFirstNSetBits(uint16_t number, unsigned short count)
{
    assert(count < sizeof(number) * 8);
    uint16_t result = 0;
    for(decltype(count) i = 0; i < count; i++) {
        auto nextBit = firstSetBit(number);
        assert(nextBit);
        result |= nextBit;
        number ^= nextBit;
    }
    return result;
}

std::optional<HighCard> getHighCard(const Cards &cards)
{
    auto distinctCards = orSuits(cards);
    return { HighCard { getFirstNSetBits(distinctCards, 5)} };
}

std::optional<OnePair> getOnePair(const Cards &cards)
{
    auto sameCards = getSameCards(cards);
    if(__builtin_popcount(sameCards) != 1) {
        return {};
    }

    auto kickers = getFirstNSetBits(orSuits(cards) ^ sameCards, 3);
    return { OnePair { static_cast<CardRank>(sameCards), kickers } };
}

std::optional<TwoPair> getTwoPair(const Cards &cards)
{
    auto sameCards = getSameCards(cards);
    if(__builtin_popcount(sameCards) < 2) {
        return {};
    }
    auto firstPair = highCard(sameCards);
    auto secondPair = highCard(static_cast<uint16_t>(~static_cast<uint16_t>(firstPair) & sameCards));
    auto ranks = orSuits(cards);
    auto kicker = highCard(static_cast<uint16_t>(~(static_cast<uint16_t>(firstPair) | static_cast<uint16_t>(secondPair)) & ranks));
    return { TwoPair { firstPair, secondPair, kicker } };
}

std::optional<Tripps> getTripps(const Cards &cards)
{
    auto sameCards = getSameCards(cards);
    auto distinctCards = orSuits(cards);
    auto potentialTripps = static_cast<uint16_t>(sameCards & xorSuits(cards));
    if(potentialTripps == 0) {
        return {};
    }

    auto kickers = getFirstNSetBits(potentialTripps ^ distinctCards, 2);
    return { Tripps {highCard(potentialTripps), CardRanks(kickers)}};
}

std::optional<Straight> getStraight(const Cards &cards)
{
    static const auto sStraightMap = getStraightMap();
    auto orCardSuits = orSuits(cards);
    for(auto it = sStraightMap.rbegin(); it != sStraightMap.rend(); it++) {
        if((orCardSuits & *it) == *it) {
            if(*it == wheelStraight()) {
                return { Straight { CardRank::Five } };
            }
            return { Straight { highCard(*it) } };
        }
    }
    return {};
}

std::optional<Flush> getFlush(const Cards &cards)
{
    const auto& allSuits = getAllSuits();
    for(auto &suit: allSuits) {
        auto suitCards = cards.getSuit(suit);
        if (__builtin_popcount(suitCards) >= 5) {
            return { Flush { CardRanks(getFirstNSetBits(suitCards, 5)), suit } };
        }
    }
    return {};
}


std::optional<FullHouse> getFullHouse(const Cards &cards)
{
    auto sameCards = getSameCards(cards);
    if (__builtin_popcount(sameCards) < 2) {
        return {};
    }

    auto potentialTripps = static_cast<uint16_t>(sameCards & xorSuits(cards));
    if(potentialTripps == 0) {
        return {};
    }

    auto numTripps = __builtin_popcount(potentialTripps);
    if(numTripps == 1) {
        auto potentialPairs = static_cast<uint16_t>(sameCards ^ potentialTripps);
        if(potentialPairs == 0) {
            return {};
        }

        auto highestPair = highCard(potentialPairs);
        return { FullHouse { static_cast<CardRank>(potentialTripps), static_cast<CardRank>(highestPair)} };
    }

    if(numTripps == 2) {
        auto topTripps = highCard(potentialTripps);
        return { FullHouse { topTripps, static_cast<CardRank>(potentialTripps ^ static_cast<uint16_t>(topTripps))} };
    }

    throw Exception("Logic error");
}

std::optional<Quads> getQuads(const Cards &cards)
{
    auto potentialQuad = static_cast<CardRank>(andSuits(cards));
    const auto &cardRankSet = getCardRankSet();
    if(cardRankSet.find(potentialQuad) != cardRankSet.end()) {
        auto kickers = xorSuits(cards);
        return { Quads { potentialQuad, highCard(kickers)} };
    }

    return {};
}

std::optional<StraightFlush> getStraightFlush(const Cards &cards)
{
    static const auto sStraightFlushes = getStraightFlushesMap();
    const auto& cardsInt = cards.internalRepresentation();
    for(auto it = sStraightFlushes.rbegin(); it != sStraightFlushes.rend(); it++) {
        if((cardsInt & it->first) == it->first) {
            assert(it->first != 0);
            if(it->first == (static_cast<uint64_t>(wheelStraight()) << static_cast<unsigned short>(it->second))) {
                return { StraightFlush { CardRank::Five, it->second } };
            }
            return { StraightFlush { highCard(it->first), it->second } };
        }
    }
    return {};
}

std::optional<RoyalFlush> getRoyalFlush(const Cards &cards)
{
    static const auto sRoyalFlushes = getRoyalFlushesMap();
    const auto& cardsInt = cards.internalRepresentation();
    for(const auto &royalFlush: sRoyalFlushes) {
        if((cardsInt & royalFlush.first) == royalFlush.first) {
            return { RoyalFlush { royalFlush.second } };
        }
    }
    return {};
}

//// HighCard //////////////////////////////////////////////////////////////////

bool HighCard::operator<(const struct IHandValueType& other) const
{
    const auto &thisTypeInfo = typeid(*this);
    const auto &otherTypeInfo = typeid(other);
    if(thisTypeInfo == otherTypeInfo) {
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
    if(typeid(other) == typeid(*this)) {
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

bool OnePair::operator==(const struct OnePair &other) const
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
    const auto &thisTypeInfo = typeid(*this);
    const auto &otherTypeInfo = typeid(other);
    if(thisTypeInfo == otherTypeInfo) {
        auto otherDerrived = static_cast<const OnePair&>(other);
        return *this < otherDerrived;
    }

    return sTypeInfos[thisTypeInfo.hash_code()] < sTypeInfos[otherTypeInfo.hash_code()];
}

bool OnePair::operator<(const struct OnePair &other) const
{
    if (mPair == other.mPair) {
        return mKickers < other.mKickers;
    }
    return mPair < other.mPair;
}

bool OnePair::operator==(const struct IHandValueType& other) const
{
    if(typeid(other) == typeid(*this)) {
        auto otherDerrived = static_cast<const OnePair&>(other);
        return *this == otherDerrived;
    }   
    return false;
}

//// TwoPair ///////////////////////////////////////////////////////////////////

bool TwoPair::operator==(const struct IHandValueType& other) const
{
    if(typeid(other) == typeid(*this)) {
        auto otherDerrived = static_cast<const TwoPair&>(other);
        return *this == otherDerrived;
    }   
    return false;
}

bool TwoPair::operator==(const struct TwoPair &other) const 
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
    const auto &thisTypeInfo = typeid(*this);
    const auto &otherTypeInfo = typeid(other);
    if(thisTypeInfo == otherTypeInfo) {
        auto otherDerrived = static_cast<const TwoPair&>(other);
        return *this < otherDerrived;
    }

    return sTypeInfos[thisTypeInfo.hash_code()] < sTypeInfos[otherTypeInfo.hash_code()];
}

bool TwoPair::operator<(const struct TwoPair& other) const 
{
    if (mTopPair == other.mTopPair) {
        if(mBottomPair == other.mBottomPair) {
            return mKicker < other.mKicker;
        }

        return mBottomPair < other.mBottomPair;
    }
    return mTopPair < other.mTopPair;
}

//// Tripps ///////////////////////////////////////////////////////////////////

bool Tripps::operator==(const struct IHandValueType &other) const
{
    if(typeid(*this) == typeid(other)) {
        auto otherDerrived = static_cast<const Tripps&>(other);
        return *this == otherDerrived;
    }
    return false;
}

bool Tripps::operator==(const struct Tripps &other) const
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
    const auto &thisTypeInfo = typeid(*this);
    const auto &otherTypeInfo = typeid(other);
    if(thisTypeInfo == otherTypeInfo) {
        auto otherDerrived = static_cast<const Tripps&>(other);
        return *this < otherDerrived;
    }

    return sTypeInfos[thisTypeInfo.hash_code()] < sTypeInfos[otherTypeInfo.hash_code()];
}

bool Tripps::operator<(const struct Tripps& other) const 
{
    if(mTripps == other.mTripps) {
        return mKickers < other.mKickers;
    }
    return mTripps < other.mTripps;
}

//// Straight //////////////////////////////////////////////////////////////////

bool Straight::operator==(const struct IHandValueType &other) const
{
    if(typeid(*this) == typeid(other)) {
        auto otherDerrived = static_cast<const Straight&>(other);
        return *this == otherDerrived;
    }
    return false;
}

bool Straight::operator<(const struct IHandValueType& other) const
{
    const auto &thisTypeInfo = typeid(*this);
    const auto &otherTypeInfo = typeid(other);
    if(thisTypeInfo == otherTypeInfo) {
        auto otherDerrived = static_cast<const Straight&>(other);
        return *this < otherDerrived;
    }

    return sTypeInfos[thisTypeInfo.hash_code()] < sTypeInfos[otherTypeInfo.hash_code()];
}

bool Straight::operator==(const struct Straight &other) const
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

bool Flush::operator==(const struct Flush &other) const
{
    return mCards == other.mCards && mSuit == other.mSuit;
}

std::string Flush::toString() const
{
    std::ostringstream oss;
    oss << "Flush: " << mCards.toString() << " of suit " << toStyleString(mSuit);
    return oss.str();
}

bool Flush::operator==(const struct IHandValueType &other) const
{
    if(typeid(*this) == typeid(other)) {
        auto otherDerrived = static_cast<const Flush&>(other);
        return *this == otherDerrived;
    }
    return false;
}

bool Flush::operator<(const struct IHandValueType& other) const
{
    const auto &thisTypeInfo = typeid(*this);
    const auto &otherTypeInfo = typeid(other);
    if(thisTypeInfo == otherTypeInfo) {
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

bool FullHouse::operator==(const struct IHandValueType &other) const
{
    if(typeid(*this) == typeid(other)) {
        auto otherDerrived = static_cast<const FullHouse&>(other);
        return *this == otherDerrived;
    }
    return false;
}

bool FullHouse::operator<(const struct IHandValueType& other) const
{
    const auto &thisTypeInfo = typeid(*this);
    const auto &otherTypeInfo = typeid(other);
    if(thisTypeInfo == otherTypeInfo) {
        auto otherDerrived = static_cast<const FullHouse&>(other);
        return *this < otherDerrived;
    }

    return sTypeInfos[thisTypeInfo.hash_code()] < sTypeInfos[otherTypeInfo.hash_code()];
}

bool FullHouse::operator<(const struct FullHouse& other) const
{
    if(mTripps == other.mTripps) {
        return mPair < other.mPair;
    }
    return mTripps < other.mTripps;
}

//// Quads /////////////////////////////////////////////////////////////////////

bool Quads::operator==(const struct Quads &other) const 
{
    return mQuads == other.mQuads && mKicker == other.mKicker;
}

std::string Quads::toString() const
{
    std::ostringstream oss;
    oss << "Four of a kind: " << toStyleString(mQuads) << ", " << toStyleString(mKicker) << " kicker";
    return oss.str();
}


bool Quads::operator==(const struct IHandValueType &other) const
{
    if(typeid(*this) == typeid(other)) {
        auto otherDerrived = static_cast<const Quads&>(other);
        return *this == otherDerrived;
    }
    return false;
}

bool Quads::operator<(const struct IHandValueType& other) const
{
    const auto &thisTypeInfo = typeid(*this);
    const auto &otherTypeInfo = typeid(other);
    if(thisTypeInfo == otherTypeInfo) {
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

bool StraightFlush::operator==(const struct StraightFlush &other) const 
{
    return mHighCard == other.mHighCard && mSuit == other.mSuit;
}

std::string StraightFlush::toString() const
{
    std::ostringstream oss;
    oss << "Straight flush " << toStyleString(mHighCard) << " high, " << toStyleString(mSuit);
    return oss.str();
}

bool StraightFlush::operator==(const struct IHandValueType &other) const
{
    if(typeid(*this) == typeid(other)) {
        auto otherDerrived = static_cast<const StraightFlush&>(other);
        return *this == otherDerrived;
    }
    return false;
}

bool StraightFlush::operator<(const struct IHandValueType& other) const
{
    const auto &thisTypeInfo = typeid(*this);
    const auto &otherTypeInfo = typeid(other);
    if(thisTypeInfo == otherTypeInfo) {
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

bool RoyalFlush::operator==(const struct RoyalFlush &other) const 
{
    return mSuit == other.mSuit;
}

std::string RoyalFlush::toString() const
{
    std::ostringstream oss;
    oss << "Royal flush of " << toStyleString(mSuit);
    return oss.str();
}

bool RoyalFlush::operator==(const struct IHandValueType &other) const
{
    if(typeid(*this) == typeid(other)) {
        auto otherDerrived = static_cast<const RoyalFlush&>(other);
        return *this == otherDerrived;
    }
    return false;
}

bool RoyalFlush::operator<(const struct IHandValueType& other) const
{
    const auto &thisTypeInfo = typeid(*this);
    const auto &otherTypeInfo = typeid(other);
    if(thisTypeInfo == otherTypeInfo) {
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

HandValue::HandValue(const Cards &cards)
{
    auto royalFlush = getRoyalFlush(cards);
    if(royalFlush) {
        mHandValueType = std::make_unique<RoyalFlush>(*royalFlush);
        return;
    }

    auto straightFlush = getStraightFlush(cards);
    if(straightFlush) {
        mHandValueType = std::make_unique<StraightFlush>(*straightFlush);
        return;
    }

    auto quads = getQuads(cards);
    if(quads) {
        mHandValueType = std::make_unique<Quads>(*quads);
        return;
    }

    auto fullHouse = getFullHouse(cards);
    if(fullHouse) {
        mHandValueType = std::make_unique<FullHouse>(*fullHouse);
        return;
    }

    auto flush = getFlush(cards);
    if(flush) {
        mHandValueType = std::make_unique<Flush>(*flush);
        return;
    }

    auto straight = getStraight(cards);
    if(straight) {
        mHandValueType = std::make_unique<Straight>(*straight);
        return;
    }

    auto tripps = getTripps(cards);
    if(tripps) {
        mHandValueType = std::make_unique<Tripps>(*tripps);
        return;
    }

    auto twoPair = getTwoPair(cards);
    if(twoPair) {
        mHandValueType = std::make_unique<TwoPair>(*twoPair);
        return;
    }

    auto onePair = getOnePair(cards);
    if(onePair) {
        mHandValueType = std::make_unique<OnePair>(*onePair);
        return;
    }

    auto highCard = getHighCard(cards);
    if(!highCard) {
        throw Exception("Failed to determine hand value type");
    }
    mHandValueType = std::make_unique<HighCard>(*highCard);
}

IHandValueType& HandValue::getHandValueType() const
{
    return *mHandValueType;
}
}