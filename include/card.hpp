#pragma once
#include <stdint.h>
#include <string>
#include <vector>
#include <exception>

namespace professor
{
enum class Suit: unsigned short 
{
    Spade = 0,
    Heart = 8,
    Clubs = 16,
    Diamond = 24 
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

class Card
{
public:
    Card() = default;
    Card(CardRank rank, Suit suit)
        : mInternalRepresentation(static_cast<uint16_t>(rank) << static_cast<unsigned short>(suit))
    {}

    Card(const Card& other) = default;
    Card &operator=(const Card& other) = default;

    std::string toString() const;
    uint64_t internalRepresentation() const { return mInternalRepresentation; }

private:
    uint64_t mInternalRepresentation{ 0 };
};

class Cards
{
public:
    Cards(const std::vector<Card> &cards);
    std::string toString() const;

private:
    uint64_t mInternalRepresentation { 0 };
};

}