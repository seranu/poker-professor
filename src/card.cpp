#include "card.hpp"

#include "exception.hpp"
#include <algorithm>
#include <cassert>
#include <sstream>

namespace
{
using namespace professor;
constexpr const uint64_t kRankMask = 0xffff;

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

CardRank rankFromChar(char c) {
    switch(c) {
        case '2': return CardRank::Two;
        case '3': return CardRank::Three;
        case '4': return CardRank::Four;
        case '5': return CardRank::Five;
        case '6': return CardRank::Six;
        case '7': return CardRank::Seven;
        case '8': return CardRank::Eight;
        case '9': return CardRank::Nine;
        case 'T': return CardRank::Ten;
        case 'J': return CardRank::Jack;
        case 'Q': return CardRank::Queen;
        case 'K': return CardRank::King;
        case 'A': return CardRank::Ace;
        default:
             throw Exception("Invalid card char: " + c);
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
}

Suit suitFromChar(char c)
{
    switch(c) {
        case 's': return Suit::Spade;
        case 'h': return Suit::Heart;
        case 'c': return Suit::Clubs;
        case 'd': return Suit::Diamond;
        default:
            throw Exception("Invalid suit char: " + c);
    }
}
} // anonymous namespace

namespace professor
{

std::string toStyleString(CardRank rank)
{
    switch(rank) {
        case CardRank::Two:   return "Two";
        case CardRank::Three: return "Three";
        case CardRank::Four:  return "Four";
        case CardRank::Five:  return "Five";
        case CardRank::Six:   return "Six";
        case CardRank::Seven: return "Seven";
        case CardRank::Eight: return "Eight";
        case CardRank::Nine:  return "Nine";
        case CardRank::Ten:   return "Ten";
        case CardRank::Jack:  return "Jack";
        case CardRank::Queen: return "Queen";
        case CardRank::King:  return "King";
        case CardRank::Ace:   return "Ace";
        default:
            throw Exception("Invalid rank");
    }
}
std::string toStyleString(Suit suit)
{
    switch(suit) {
        case Suit::Spade:   return "Spade";
        case Suit::Heart:   return "Heart";
        case Suit::Clubs:   return "Clubs";
        case Suit::Diamond: return "Diamond";
        default:
            throw Exception("Invalid suit");
    }
}


const std::vector<Suit> &getAllSuits()
{
    static const std::vector<Suit> sAllSuits = { Suit::Spade, Suit::Heart, Suit::Clubs, Suit::Diamond };
    return sAllSuits;
}
const std::vector<CardRank> &getAllCardRanks()
{
    static const std::vector<CardRank> sAllCardRanks = {
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
    return sAllCardRanks;
}

const std::unordered_set<CardRank> &getCardRankSet()
{
    static const std::unordered_set<CardRank> sCardRankMap(getAllCardRanks().begin(), getAllCardRanks().end());
    return sCardRankMap;
}

std::string Card::toString() const
{
    for(Suit suit: getAllSuits())
    {
        uint64_t mask = kRankMask << static_cast<unsigned short>(suit);
        uint64_t maybeRank = mInternalRepresentation & mask;
        if(maybeRank) {
            CardRank rank = static_cast<CardRank>(maybeRank >> static_cast<unsigned short>(suit));
            return "[" + ::toString(rank) + ::toString(suit) + "]";
        }
    }
    throw Exception("Unknown card");
}

Cards::Cards(const std::vector<Card> &cards)
{
    for(const auto &card: cards) {
        assert(0 == (mInternalRepresentation & card.internalRepresentation()));
        mInternalRepresentation |= card.internalRepresentation();
    }
}

void Cards::add(Card card)
{
    assert(!(mInternalRepresentation & card.internalRepresentation()));
    mInternalRepresentation |= card.internalRepresentation();
}

void Cards::add(Cards cards)
{
    assert(!(mInternalRepresentation & cards.internalRepresentation()));
    mInternalRepresentation |= cards.internalRepresentation();
}


void Cards::add(const std::vector<Card> &cards)
{
    for(const auto &card: cards) {
        add(card);
    }
}

bool Cards::operator< (const Cards& other) const
{
    return mInternalRepresentation < other.mInternalRepresentation;
}

bool Cards::operator==(const Cards& other) const
{
    return mInternalRepresentation == other.mInternalRepresentation;
}

std::optional<Cards> Cards::fromString(const std::string &cardsStr)
{
    const char kDelim = ' ';
    if(cardsStr.empty()) {
        return {};
    }

    size_t start;
    size_t end = 0;
    std::vector<Card> cards;
    while((start = cardsStr.find_first_not_of(kDelim, end)) != std::string::npos) {
        end = cardsStr.find(kDelim, start);
        //assert((end - start) == 2);
        cards.emplace_back(rankFromChar(cardsStr[start]), suitFromChar(cardsStr[start + 1]));
    }
    if (cards.empty()) {
        return {};
    }
    return Cards(cards);
}



std::string Cards::toString() const
{
    std::string result("[");
    const auto &allSuits = getAllSuits();
    const auto &allRanks = getAllCardRanks();
    bool first = true;
    std::for_each(allSuits.begin(), allSuits.end(), [&] (const Suit &suit) {
        uint64_t mask = kRankMask << static_cast<unsigned short>(suit);
        uint16_t suitCards = (mInternalRepresentation & mask) >> static_cast<unsigned short>(suit);
        std::for_each(allRanks.begin(), allRanks.end(), [&] (const CardRank &rank) {
            if(suitCards & static_cast<uint16_t>(rank)) {
                if(!first) {
                    result += " ";
                }
                first = false;
                result += ::toString(rank) + ::toString(suit);
            }
        });
    });
    result += "]";
    return result;
}

uint16_t Cards::getSuit(Suit suit) const
{
    return static_cast<uint16_t>(mInternalRepresentation >> static_cast<unsigned short>(suit));
}

CardRanks::CardRanks(const std::vector<CardRank> &ranks)
{
    for(auto rank: ranks) {
        assert(0 == (mInternalRepresentation & static_cast<uint16_t>(rank)));
        mInternalRepresentation |= static_cast<uint16_t>(rank);
    }
}

std::string CardRanks::toString() const
{
    std::ostringstream oss;
    const auto &allRanks = getAllCardRanks();
    bool first = true;
    for(const auto &rank: allRanks) {
        if(static_cast<uint16_t>(rank) & mInternalRepresentation) {
            if (!first) {
                oss << " ";
            }
            oss << ::toString(rank);
            first = false;
        }
    }
    return oss.str();
}


} // namespace professor
