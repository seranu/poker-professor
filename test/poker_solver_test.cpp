#include "catch.hpp"
#include "poker_solver.hpp"
#include "player.hpp"

using namespace professor;
TEST_CASE("Poker solver test")
{
    Player playerOne("Serban");
    Player playerTwo("Tibi");

    playerOne.setCards(Cards::fromString("2h Ad"));
    playerTwo.setCards(Cards::fromString("Ah Jc"));
    std::vector<Player> players;
    players.push_back(playerOne);
    players.push_back(playerTwo);

    PokerSolver solver;
    auto result = solver.solve(players, *Cards::fromString("6h 3c 5c 8c 6d"));

    CHECK(result[0] == 0);
    CHECK(result[1] == 100);
}