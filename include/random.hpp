#pragma once
#include <memory>
#include <vector>
#include <algorithm>
#include <random>

namespace professor
{
class Random
{
public:
    Random();
    int number(int min, int max);

    template<class T, int N>
    void shuffle(std::array<T, N> &deck)
    { std::shuffle(deck.begin(), deck.end(), mGenerator); }
    template<typename T>
    void shuffle(std::vector<T> &deck)
    { std::shuffle(deck.begin(), deck.end(), mGenerator); }
    static std::shared_ptr<Random> get()
    {
        static std::shared_ptr<Random> sInstance;
        if(!sInstance) {
            sInstance = std::make_shared<Random>();
        }
        return sInstance;
    }
private:
    std::default_random_engine mGenerator;
    std::uniform_real_distribution<double> mDistribution;
};
}