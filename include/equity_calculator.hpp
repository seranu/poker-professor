#pragma once
#include "card.hpp"

namespace professor {
struct EquityResult {
    double heroEquity { 0 };
    double villainEquity { 0 };
    double draw { 0 };
};

class EquityCalculator {
public:
    EquityCalculator() = default;
    EquityResult calculateEquity(Cards heroHand, Cards villanHand, int numRuns);

private:
};
}