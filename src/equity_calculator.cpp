#include "equity_calculator.hpp"
#include "deck.hpp"
#include "board.hpp"

namespace professor
{
EquityResult EquityCalculator::calculateEquity(Hand heroHand, Hand villanHand, int numRuns)
{
    for(auto i = 0; i < numRuns; i++) {

        Deck deck;
        Board board(std::move(deck));
        board.drawFlop();
        board.drawTurn();
        board.drawRiver();

        std::vector<Hand> hands;
        std::vector<
    }
}

}