#pragma once
#include "card.hpp"
#include "player.hpp"

#include <vector>

namespace professor {
class PokerSolver {
public:
    std::vector<double> solve(const std::vector<Player>& playerCards, const Cards& cards);
};
}
