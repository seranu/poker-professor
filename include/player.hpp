#pragma once
#include <string>
#include <optional>

#include "card.hpp"

namespace professor
{
class Player
{
public:
    Player(std::string name)
        : mName(std::move(name))
        , mChips(0)
        {}    
    
    void setCards(std::optional<Cards> cards)
        { mCards = cards; }

    std::optional<Cards> getCards() const
        { return mCards; }

    std::string toString() const;

private:
    std::string mName;
    double mChips;
    std::optional<Cards> mCards;
};
}