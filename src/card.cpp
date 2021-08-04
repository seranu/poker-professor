#include "card.hpp"

#include "exception.hpp"

namespace
{
using namespace professor;
constexpr const uint16_t kRankMask = 0xffffffffffffffff;
const Suit AllSuits[] = { Suit::Spade, Suit::Heart, Suit::Clubs, Suit::Diamond };
const CardRank AllCardRanks[] = {
        CardRank::Two,
        CardRank::Three,
        CardRank::Four,
        CardRank::Five,
        CardRank::Six,
        CardRank::Seven,
        CardRank::Eight,
        CardRank::Nine,
        CardRank::Ten,
        CardRank::Jack,
        CardRank::Queen,
        CardRank::King,
        CardRank::Ace
    };
}

std::string toString(CardRank rank)
{
    switch(rank) {
        case CardRank::Two:   return "2";
        case CardRank::Three: return "3";
        case CardRank::Four:  return "4";
        case CardRank::Five:  return "5";
        case CardRank::Six:   return "6";
        case CardRank::Seven: return "7";
        case CardRank::Eight: return "8";
        case CardRank::Nine:  return "9";
        case CardRank::Ten:   return "T";
        case CardRank::Jack:  return "J";
        case CardRank::Queen: return "Q";
        case CardRank::King:  return "K";
        case CardRank::Ace:   return "A";
        default:
            throw Exception("Invalid card rank");
    }
}

std::string toString(Suit suit)
{
    switch(suit) {
        case Suit::Spade:   return "s";
        case Suit::Heart:   return "h";
        case Suit::Clubs:   return "c";
        case Suit::Diamond: return "d";
        default:
            throw Exception("Invalid suit");
    }
};
}

namespace professor
{
std::string Card::toString() const
{
    for(Suit suit: AllSuits)
    {
        uint64_t mask = kRankMask << static_cast<unsigned short>(suit);
        uint64_t maybeRank = mInternalRepresentation & mask;
        if(maybeRank) {
            CardRank rank = static_cast<CardRank>(maybeRank);
            return "[ " + ::toString(rank) + ::toString(static_cast<Suit>(i)) + "]";
        }
    }
}

Cards::Cards(const std::vector<Card> &cards)
{
    for(const auto &card: cards) {
        mInternalRepresentation |= card.internalRepresentation();
    }
}

std::string Cards::toString() const
{
    std::string result("[");
    for_each(std::begin(AllSuits), std::end(AllSuits), [&result] (const Suit &suit) {
        uint64_t mask = kRankMask << suit;
        uint16_t suitCards = mInternalRepresentation & mask;
        for_each(std::begin(AllCardRanks), std::end(AllCardRanks), [&] (const CardRank &rank) {
            if(suitCards & static_cast<uint16_t>(rank)) {
                result += toString(rank) + toString(suit) + " ";
            }
        });
    });
    result += "]";
    return result;
}

}