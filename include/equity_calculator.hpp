#pragma once
#include "types.hpp"

namespace professor
{
struct EquityResult
{
    double heroEquity { 0 };
    double villainEquity { 0 };
    double draw{ 0 };
};

class EquityCalculator
{
public:
    EquityCalculator() = default;
    EquityResult calculateEquity(Hand heroHand, Hand villanHand, int numRuns);
private:
};
}