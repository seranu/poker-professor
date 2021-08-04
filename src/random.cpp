#include "random.hpp"

#include <chrono>
#include <random>
#include <algorithm>

namespace professor
{
Random::Random() 
    : mGenerator(std::default_random_engine(std::chrono::system_clock::now().time_since_epoch().count())) 
    , mDistribution(0, 1)
{
}
    
int Random::number(int min, int max)
{
    double r = mDistribution(mGenerator);

    return r * (max - min) + min;
}
}