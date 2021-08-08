#include "board.hpp"

namespace professor
{
void Board::reset()
{
    mFlop.reset();
    mTurn.reset();
    mRiver.reset();
}

void Board::drawFlop(Deck &deck)
{
    mFlop = Cards({ deck.draw(), deck.draw(), deck.draw() });
}

void Board::drawTurn(Deck &deck)
{
    mTurn = deck.draw();
}

void Board::drawRiver(Deck &deck)
{
    mRiver = deck.draw();
}

Cards Board::getBoard() const
{
    Cards cards(*mFlop);
    cards.add(*mTurn);
    cards.add(*mRiver);
    return cards;
}

}