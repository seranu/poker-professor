#include "card.hpp"
#include "catch.hpp"

using namespace professor;
struct CardExpectation {
    CardExpectation(CardRank r, Suit s, std::string name)
        : rank(r)
        , suit(s)
        , cardName(name)
    {
    }
    CardRank rank;
    Suit suit;
    std::string cardName;
};

TEST_CASE("Card test")
{
    auto expectation = GENERATE(
        CardExpectation { CardRank::Ace, Suit::Spade, "[As]" },
        CardExpectation { CardRank::King, Suit::Spade, "[Ks]" },
        CardExpectation { CardRank::Queen, Suit::Spade, "[Qs]" },
        CardExpectation { CardRank::Jack, Suit::Spade, "[Js]" },
        CardExpectation { CardRank::Ten, Suit::Spade, "[Ts]" },
        CardExpectation { CardRank::Nine, Suit::Spade, "[9s]" },
        CardExpectation { CardRank::Eight, Suit::Spade, "[8s]" },
        CardExpectation { CardRank::Seven, Suit::Spade, "[7s]" },
        CardExpectation { CardRank::Six, Suit::Spade, "[6s]" },
        CardExpectation { CardRank::Five, Suit::Spade, "[5s]" },
        CardExpectation { CardRank::Four, Suit::Spade, "[4s]" },
        CardExpectation { CardRank::Three, Suit::Spade, "[3s]" },
        CardExpectation { CardRank::Two, Suit::Spade, "[2s]" },

        CardExpectation { CardRank::Ace, Suit::Clubs, "[Ac]" },
        CardExpectation { CardRank::King, Suit::Clubs, "[Kc]" },
        CardExpectation { CardRank::Queen, Suit::Clubs, "[Qc]" },
        CardExpectation { CardRank::Jack, Suit::Clubs, "[Jc]" },
        CardExpectation { CardRank::Ten, Suit::Clubs, "[Tc]" },
        CardExpectation { CardRank::Nine, Suit::Clubs, "[9c]" },
        CardExpectation { CardRank::Eight, Suit::Clubs, "[8c]" },
        CardExpectation { CardRank::Seven, Suit::Clubs, "[7c]" },
        CardExpectation { CardRank::Six, Suit::Clubs, "[6c]" },
        CardExpectation { CardRank::Five, Suit::Clubs, "[5c]" },
        CardExpectation { CardRank::Four, Suit::Clubs, "[4c]" },
        CardExpectation { CardRank::Three, Suit::Clubs, "[3c]" },
        CardExpectation { CardRank::Two, Suit::Clubs, "[2c]" },

        CardExpectation { CardRank::Ace, Suit::Heart, "[Ah]" },
        CardExpectation { CardRank::King, Suit::Heart, "[Kh]" },
        CardExpectation { CardRank::Queen, Suit::Heart, "[Qh]" },
        CardExpectation { CardRank::Jack, Suit::Heart, "[Jh]" },
        CardExpectation { CardRank::Ten, Suit::Heart, "[Th]" },
        CardExpectation { CardRank::Nine, Suit::Heart, "[9h]" },
        CardExpectation { CardRank::Eight, Suit::Heart, "[8h]" },
        CardExpectation { CardRank::Seven, Suit::Heart, "[7h]" },
        CardExpectation { CardRank::Six, Suit::Heart, "[6h]" },
        CardExpectation { CardRank::Five, Suit::Heart, "[5h]" },
        CardExpectation { CardRank::Four, Suit::Heart, "[4h]" },
        CardExpectation { CardRank::Three, Suit::Heart, "[3h]" },
        CardExpectation { CardRank::Two, Suit::Heart, "[2h]" },

        CardExpectation { CardRank::Ace, Suit::Diamond, "[Ad]" },
        CardExpectation { CardRank::King, Suit::Diamond, "[Kd]" },
        CardExpectation { CardRank::Queen, Suit::Diamond, "[Qd]" },
        CardExpectation { CardRank::Jack, Suit::Diamond, "[Jd]" },
        CardExpectation { CardRank::Ten, Suit::Diamond, "[Td]" },
        CardExpectation { CardRank::Nine, Suit::Diamond, "[9d]" },
        CardExpectation { CardRank::Eight, Suit::Diamond, "[8d]" },
        CardExpectation { CardRank::Seven, Suit::Diamond, "[7d]" },
        CardExpectation { CardRank::Six, Suit::Diamond, "[6d]" },
        CardExpectation { CardRank::Five, Suit::Diamond, "[5d]" },
        CardExpectation { CardRank::Four, Suit::Diamond, "[4d]" },
        CardExpectation { CardRank::Three, Suit::Diamond, "[3d]" },
        CardExpectation { CardRank::Two, Suit::Diamond, "[2d]" });

    Card c(expectation.rank, expectation.suit);
    CHECK(c.toString() == expectation.cardName);
}