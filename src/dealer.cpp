#include "dealer.hpp"
#include "poker_solver.hpp"
#include "log.hpp"
#include <sstream>

namespace
{
using namespace professor;
std::string toString(const std::vector<Player> &players)
{
    std::ostringstream oss;
    for(decltype(players.size()) i = 0; i < players.size(); i++) {
        oss << "Player " << i << ": " << players[i].toString() << "\n";
    }
    return oss.str();
}
}
namespace professor
{
Dealer::Dealer(const std::vector<Player> &players)
    : mPlayers(players)
{
    PP_LOG_DEBUG("Dealer::Dealer()");
    auto playersStr = toString(mPlayers);
    PP_LOG_DEBUG("Players: \n%s", playersStr.c_str());
}

void Dealer::dealPlayerCards()
{
    PP_LOG_DEBUG("Dealing cards");
    for(auto &player: mPlayers) {
        auto firstCard = mDeck.draw();
        auto secondCard = mDeck.draw();
        player.setCards(Cards({firstCard, secondCard}));
    }
    PP_LOG_DEBUG("Players: \n%s", toString(mPlayers).c_str());
}

void Dealer::dealFlop()
{
    mBoard.drawFlop(mDeck);
    PP_LOG_DEBUG("Flop: %s", mBoard.mFlop->toString().c_str());
}

void Dealer::dealTurn()
{
    mBoard.drawTurn(mDeck);
    PP_LOG_DEBUG("Turn: %s", mBoard.mTurn->toString().c_str());
}

void Dealer::dealRiver()
{
    mBoard.drawRiver(mDeck);
    PP_LOG_DEBUG("River: %s", mBoard.mRiver->toString().c_str());
}

std::vector<double> Dealer::evaluate()
{
    PokerSolver solver;
    std::vector<double> results = solver.solve(mPlayers, mBoard.getBoard());
    for(decltype(results.size()) i = 0; i < results.size(); i++) {
        PP_LOG_DEBUG("Player %s: equity: %.3f", mPlayers[i].toString().c_str(), results[i]);
    }

    return results;
}

std::vector<double> Dealer::doOneRound()
{
    mDeck.reset();
    dealPlayerCards();
    dealFlop();
    dealTurn();
    dealRiver();
    return evaluate();
}


}