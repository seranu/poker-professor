#include "catch.hpp"
#include "card.hpp"

using namespace professor;
TEST_CASE("Card test")
{
    Card c(CardRank::Ace, Suit::Clubs);
    CHECK(c.toString() == "[Ac]");

}
