#include "poker_solver.hpp"
#include <stdint.h>

namespace professor
{
std::optional<HighCard> getHighCard(const Cards &cards)
{
    auto spades = cards.getSuit(Suit::Spade);
    auto hearts = cards.getSuit(Suit::Heart);
    auto clubs  = cards.getSuit(Suit::Clubs);
    auto diamonds = cards.getSuit(Suit::Diamond); 

    // TODO: check for fullHouse?
    auto pairs = (spades & hearts) | (spades & clubs) | (spades & diamonds)
        | (hearts & clubs) | (hearts & diamonds) | (clubs & diamonds);
    auto distinctCards = spades | hearts | clubs | diamonds;
    
    return { distinctCards ^ pairs };
}

std::optional<OnePair> getOnePair(const Cards &cards)
{
    auto spades = cards.getSuit(Suit::Spade);
    auto hearts = cards.getSuit(Suit::Heart);
    auto clubs  = cards.getSuit(Suit::Clubs);
    auto diamonds = cards.getSuit(Suit::Diamond); 

    // TODO: need to check for tripps or quads?
    
    auto pairs = (spades & hearts) | (spades & clubs) | (spades & diamonds)
        | (hearts & clubs) | (hearts & diamonds) | (clubs & diamonds);

   
    return 


}
std::optional<TwoPair> getTwoPair(const Cards &cards);
std::optional<Tripps> getTripps(const Cards &cards);
std::optional<Straight> getStraight(const Cards &cards);
std::optional<Flush> getFlush(const Cards &cards);
std::optional<FullHouse> getFullHouse(const Cards &cards);
std::optional<Quads> getQuads(const Cards &cards);
std::optional<StraightFlush> getStraightFlush(const Cards &cards);
std::optional<RoyalFlush> getRoyalFlush(const Cards &cards);

HandValue::HandValue(const Cards &cards)
{
}

HandValueType HandValue::getHandValueType() const
{
    return {};
}

PokerResult PokerSolver::solve()
{
    return {};
}

}
