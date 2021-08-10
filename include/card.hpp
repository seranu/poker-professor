#pragma once
#include <stdint.h>
#include <string>
#include <vector>
#include <exception>
#include <unordered_set>
#include <optional>
#include <functional>

namespace professor
{
enum class Suit: unsigned short 
{
    Spade = 0,
    Heart = 16,
    Clubs = 32,
    Diamond = 48 
};

enum class CardRank: uint16_t
{
    Two   = 1,
    Three = 1 << 1,
    Four  = 1 << 2,
    Five  = 1 << 3,
    Six   = 1 << 4,
    Seven = 1 << 5,
    Eight = 1 << 6,
    Nine  = 1 << 7,
    Ten   = 1 << 8,
    Jack  = 1 << 9,
    Queen = 1 << 10,
    King  = 1 << 11,
    Ace   = 1 << 12
};

std::string toStyleString(CardRank rank);
std::string toStyleString(Suit suit);

const std::vector<Suit>& getAllSuits();
const std::vector<CardRank>& getAllCardRanks();
const std::unordered_set<CardRank>& getCardRankSet();

class Card
{
public:
    Card() = default;
    Card(CardRank rank, Suit suit)
        : mInternalRepresentation(static_cast<uint64_t>(rank) << static_cast<unsigned short>(suit))
    {}

    explicit Card(uint64_t internalRepresentation)
        : mInternalRepresentation(internalRepresentation)
    {
    }

    Card(const Card& other) = default;
    Card &operator=(const Card& other) = default;
    bool operator==(const Card& other) const
        { return mInternalRepresentation == other.mInternalRepresentation; }

    std::string toString() const;
    inline uint64_t internalRepresentation() const { return mInternalRepresentation; }

private:
    uint64_t mInternalRepresentation{ 0 };
};

class Cards
{
public:
    explicit Cards(const std::vector<Card> &cards);

    explicit Cards(uint64_t cards)
        : mInternalRepresentation(cards)
        {}

    std::string toString() const;
    inline uint64_t internalRepresentation() const { return mInternalRepresentation; }
    inline uint16_t getSuit(Suit suit) const
    {
        return static_cast<uint16_t>(mInternalRepresentation >> static_cast<unsigned short>(suit));
    }


    void add(Card card);
    void add(Cards cards);
    void add(const std::vector<Card> &cards);
    bool operator< (const Cards& other) const;
    bool operator==(const Cards& other) const;
    static std::optional<Cards> fromString(const std::string &cardsStr);
    static void forEachCard(std::function<void(Card)> cb);

private:
    uint64_t mInternalRepresentation { 0 };
};

class CardRanks
{
public:
    CardRanks(const uint16_t ranks)
        : mInternalRepresentation(ranks)
        {}
    
    CardRanks(const std::vector<CardRank> &ranks);
    inline uint16_t internalRepresentation() const { return mInternalRepresentation; }
    bool operator==(const CardRanks &other) const {
        return mInternalRepresentation == other.mInternalRepresentation;
    }
    bool operator< (const CardRanks &other) const {
        return mInternalRepresentation < other.mInternalRepresentation;
    }

    std::string toString() const;
private:
    uint16_t mInternalRepresentation { 0 };
};

} // namespace professor
