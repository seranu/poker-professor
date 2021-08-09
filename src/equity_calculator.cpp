#include "equity_calculator.hpp"
#include "poker_solver.hpp"
#include "deck.hpp"
#include "player.hpp"
#include "board.hpp"
#include "log.hpp"
#include <algorithm>

namespace professor
{
Deck getDeckWithoutCards(Cards cards)
{
    std::vector<Card> result;
    Cards::forEachCard([&](Card card){
        if(!(card.internalRepresentation() & cards.internalRepresentation())) {
            result.emplace_back(std::move(card));
        }
    });
    return result;
}

EquityResult EquityCalculator::calculateEquity(Cards heroHand, Cards villanHand, int numRuns)
{
    SCOPE_TIMER("calculate equity");
    std::vector<Player> players;
    players.emplace_back("Hero");
    players.emplace_back("Villan");
    players[0].setCards(heroHand);
    players[1].setCards(villanHand);
    PokerSolver solver;
    auto startingDeck = getDeckWithoutCards(Cards(heroHand.internalRepresentation() | villanHand.internalRepresentation()));
    std::vector<double> totalEquities(players.size(), 0.0);
    for(auto i = 0; i < numRuns; i++) {
        Deck deck(startingDeck);
        deck.reset(); 
        PP_LOG_DEBUG("Run %d", i);
        Board board;
        board.drawFlop(deck);
        board.drawTurn(deck);
        board.drawRiver(deck);
        auto results = solver.solve(players, board.getBoard());
        for(decltype(results.size()) i = 0; i < results.size(); i++) {
            totalEquities[i] += results[i]; 
        }
    }

    for(auto &value: totalEquities) {
        value = value / numRuns;
    }

    return EquityResult { totalEquities[0], totalEquities[1], 0.0 /* TODO: draw equity */ };
}
}