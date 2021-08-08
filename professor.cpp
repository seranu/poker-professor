#include "dealer.hpp"

using namespace professor;
int main(int argc, char* argv[])
{

    std::vector<Player> players;
    players.emplace_back("Serban");
    players.emplace_back("Tibi");
    Dealer d(players);
    d.doOneRound();
    return 0;
}