#include "poker_solver.hpp"
#include "hand_value.hpp"
#include "log.hpp"
#include <algorithm>

namespace professor
{
std::vector<double> PokerSolver::solve(const std::vector<Player> &players, const Cards &board)
{
    std::vector<double> results(players.size(), 0.0);
    std::vector<std::pair<HandValue, int>> handValues;
    for(decltype(players.size()) i = 0; i < players.size(); i++) {
        Cards cards = board;
        cards.add(*players[i].getCards());
        handValues.emplace_back(HandValue(cards), i);
    }

    std::sort(handValues.begin(), handValues.end(), [] (const std::pair<HandValue, int> &lhs, const std::pair<HandValue, int> &rhs) {
        return lhs.first.getHandValueType() > rhs.first.getHandValueType();
    });

    std::vector<int> winners;
    bool isWinner = true;
    PP_LOG_INFO("Board: %s", board.toString().c_str());

    for(decltype(handValues.size()) i = 0; i < handValues.size(); i++) {
        PP_LOG_INFO("Player %s: hand value: %s", players[handValues[i].second].toString().c_str(), handValues[i].first.getHandValueType().toString().c_str());
        if (isWinner) {
            PP_LOG_INFO("Found winner: player %d", handValues[i].second);
            winners.push_back(handValues[i].second);
            if(i != handValues.size() - 1 &&
                handValues[i].first.getHandValueType() != handValues[i+1].first.getHandValueType()) 
            {
                isWinner = false;
            }
            isWinner = false;
        }
    }

    PP_LOG_INFO("Found %zu winners", winners.size());
    const double equity = 100.0 / winners.size();
    for(decltype(winners.size()) i = 0; i < winners.size(); i++) {
        results[winners[i]] = equity;
    }

    return results;
}
}
