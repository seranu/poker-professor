#include "catch.hpp"
#include "card.hpp"
#include "poker_solver.hpp"

using namespace professor;
struct CardExpectation
{
    CardExpectation(CardRank r, Suit s, std::string name)
        : rank(r)
        , suit(s)
        , cardName(name)
    {}
    CardRank rank;
    Suit suit;
    std::string cardName;
};

struct RoyalFlushExpectation
{
    Cards mCards;
    RoyalFlush mRoyalFlush;
};

struct StraightFlushExpectation
{
    Cards mCards;
    StraightFlush mStraightFlush;
};

struct QuadsExpectation
{
    Cards mCards;
    Quads mQuads;
};
struct FullHouseExpectation
{
    Cards mCards;
    FullHouse mFullHouse;
};

struct FlushExpectation
{
    Cards mCards;
    Flush mFlush;
};

struct StraightExpectation
{
    Cards mCards;
    Straight mStraight;
};

struct TrippsExpectation
{
    Cards mCards;
    Tripps mTripps;
};

struct TwoPairExpecatation
{
    Cards mCards;
    TwoPair mTwoPair;
};

struct OnePairExpectation
{
    Cards mCards;
    OnePair mOnePair;
};

struct HighCardExpectation
{
    Cards mCards;
    HighCard mHighCard;
};

TEST_CASE("Card test")
{
    auto expectation = GENERATE(
        CardExpectation{CardRank::Ace,   Suit::Spade, "[As]"},
        CardExpectation{CardRank::King,  Suit::Spade, "[Ks]"},
        CardExpectation{CardRank::Queen, Suit::Spade, "[Qs]"},
        CardExpectation{CardRank::Jack,  Suit::Spade, "[Js]"},
        CardExpectation{CardRank::Ten,   Suit::Spade, "[Ts]"},
        CardExpectation{CardRank::Nine,  Suit::Spade, "[9s]"},
        CardExpectation{CardRank::Eight, Suit::Spade, "[8s]"},
        CardExpectation{CardRank::Seven, Suit::Spade, "[7s]"},
        CardExpectation{CardRank::Six,   Suit::Spade, "[6s]"},
        CardExpectation{CardRank::Five,  Suit::Spade, "[5s]"},
        CardExpectation{CardRank::Four,  Suit::Spade, "[4s]"},
        CardExpectation{CardRank::Three, Suit::Spade, "[3s]"},
        CardExpectation{CardRank::Two,   Suit::Spade, "[2s]"},

        CardExpectation{CardRank::Ace,   Suit::Clubs, "[Ac]"},
        CardExpectation{CardRank::King,  Suit::Clubs, "[Kc]"},
        CardExpectation{CardRank::Queen, Suit::Clubs, "[Qc]"},
        CardExpectation{CardRank::Jack,  Suit::Clubs, "[Jc]"},
        CardExpectation{CardRank::Ten,   Suit::Clubs, "[Tc]"},
        CardExpectation{CardRank::Nine,  Suit::Clubs, "[9c]"},
        CardExpectation{CardRank::Eight, Suit::Clubs, "[8c]"},
        CardExpectation{CardRank::Seven, Suit::Clubs, "[7c]"},
        CardExpectation{CardRank::Six,   Suit::Clubs, "[6c]"},
        CardExpectation{CardRank::Five,  Suit::Clubs, "[5c]"},
        CardExpectation{CardRank::Four,  Suit::Clubs, "[4c]"},
        CardExpectation{CardRank::Three, Suit::Clubs, "[3c]"},
        CardExpectation{CardRank::Two,   Suit::Clubs, "[2c]"},

        CardExpectation{CardRank::Ace,   Suit::Heart, "[Ah]"},
        CardExpectation{CardRank::King,  Suit::Heart, "[Kh]"},
        CardExpectation{CardRank::Queen, Suit::Heart, "[Qh]"},
        CardExpectation{CardRank::Jack,  Suit::Heart, "[Jh]"},
        CardExpectation{CardRank::Ten,   Suit::Heart, "[Th]"},
        CardExpectation{CardRank::Nine,  Suit::Heart, "[9h]"},
        CardExpectation{CardRank::Eight, Suit::Heart, "[8h]"},
        CardExpectation{CardRank::Seven, Suit::Heart, "[7h]"},
        CardExpectation{CardRank::Six,   Suit::Heart, "[6h]"},
        CardExpectation{CardRank::Five,  Suit::Heart, "[5h]"},
        CardExpectation{CardRank::Four,  Suit::Heart, "[4h]"},
        CardExpectation{CardRank::Three, Suit::Heart, "[3h]"},
        CardExpectation{CardRank::Two,   Suit::Heart, "[2h]"},

        CardExpectation{CardRank::Ace,   Suit::Diamond, "[Ad]"},
        CardExpectation{CardRank::King,  Suit::Diamond, "[Kd]"},
        CardExpectation{CardRank::Queen, Suit::Diamond, "[Qd]"},
        CardExpectation{CardRank::Jack,  Suit::Diamond, "[Jd]"},
        CardExpectation{CardRank::Ten,   Suit::Diamond, "[Td]"},
        CardExpectation{CardRank::Nine,  Suit::Diamond, "[9d]"},
        CardExpectation{CardRank::Eight, Suit::Diamond, "[8d]"},
        CardExpectation{CardRank::Seven, Suit::Diamond, "[7d]"},
        CardExpectation{CardRank::Six,   Suit::Diamond, "[6d]"},
        CardExpectation{CardRank::Five,  Suit::Diamond, "[5d]"},
        CardExpectation{CardRank::Four,  Suit::Diamond, "[4d]"},
        CardExpectation{CardRank::Three, Suit::Diamond, "[3d]"},
        CardExpectation{CardRank::Two,   Suit::Diamond, "[2d]"}
    );

    Card c(expectation.rank, expectation.suit);
    CHECK(c.toString() == expectation.cardName);
}

TEST_CASE("Poker solver test")
{
    SECTION("Royal flushes")
    {
        SECTION("Positive")
        {
            auto cards = GENERATE(
               RoyalFlushExpectation { *Cards::fromString("2d Kd Ad Td Qd 3h Jd"), RoyalFlush { Suit::Diamond } },
               RoyalFlushExpectation { *Cards::fromString("Ah 9h Th Qh Kh 8d Jh"), RoyalFlush { Suit::Heart } },
               RoyalFlushExpectation { *Cards::fromString("Tc Jc Qc Kc Ac 9h 2d"), RoyalFlush { Suit::Clubs } },
               RoyalFlushExpectation { *Cards::fromString("5d 6h Ks Js Qs As Ts"), RoyalFlush { Suit::Spade } }
            );

            auto royalFlush = getRoyalFlush(cards.mCards);
            REQUIRE(royalFlush);
            CHECK(*royalFlush == cards.mRoyalFlush);
        }

        SECTION("Negative")
        {
            auto cards = GENERATE(
                *Cards::fromString("Ac Kc Qd Jc Tc 5d Qh"),
                *Cards::fromString("Ac Kc Qc Jc 9c 8c 7c"),
                *Cards::fromString("Kh Qh Jh Th 9h 8h 7h"),
                *Cards::fromString("Th 8s 8c 5d Ts Jc 6s")
            );

            CHECK(!getRoyalFlush(cards));
        }
    }

    SECTION("Straight flushes")
    {
        SECTION("Positive")
        {
            auto cards = GENERATE(
                StraightFlushExpectation{ *Cards::fromString("As 2s 3s 4s 5s 9d Kd"), StraightFlush { CardRank::Five, Suit::Spade } },
                StraightFlushExpectation{ *Cards::fromString("4d 5d 6d 7d 8d Kh Ac"), StraightFlush { CardRank::Eight, Suit::Diamond } },
                StraightFlushExpectation{ *Cards::fromString("6h 7h 8h 9h Th Jh Qh"), StraightFlush { CardRank::Queen, Suit::Heart } },
                StraightFlushExpectation{ *Cards::fromString("Kc Qc Jc Tc 9c 2d 3h"), StraightFlush { CardRank::King, Suit::Clubs } }
            );

            auto straightFlush = getStraightFlush(cards.mCards);
            REQUIRE(straightFlush);
            CHECK(*straightFlush == cards.mStraightFlush);
        }
        SECTION("Negative")
        {
            auto cards = GENERATE(
                *Cards::fromString("9c 8c 7d 6c 5c 2s 5s"),
                *Cards::fromString("Qc Jc Tc 9c 7c 3c 3s"),
                *Cards::fromString("2c 9d Js Jc 9c Jd 6c"),
                *Cards::fromString("Ah Kh Qh Jh Th 3d 8d")
            );
        }
    }

    SECTION("Quads")
    {
        SECTION("Positive") {
            auto cards = GENERATE(
                QuadsExpectation { *Cards::fromString("As Ad Jc Ah Kd 2s Ac"), Quads { CardRank::Ace, CardRank::King } },
                QuadsExpectation { *Cards::fromString("Js 3d 2d 2h 9d 2s 2c"), Quads { CardRank::Two, CardRank::Jack } }
            );
            auto quads = getQuads(cards.mCards);
            REQUIRE(quads);
            CHECK(*quads == cards.mQuads);
        }

        SECTION("Negative") {
            auto cards = GENERATE(Cards::fromString("Js 3d 2d Qh 9d 2s 2c"),
                                    Cards::fromString("8s 3d 2d Qh 7d As 2c"), 
                                    Cards::fromString("Js Jd Kd Kh 9d Ks Jc"),
                                    Cards::fromString("2s 3d 4d 5h 6d 7s 8c"),
                                    Cards::fromString("Js 3s 2s Qs 9s 5s 4s"),
                                    Cards::fromString("As 8d 2d Qh 9d 2s 2c"));
            CHECK(!getQuads(*cards));
        }
    }

    SECTION("Full house") {
        SECTION("Positive") {
            auto cards = GENERATE( FullHouseExpectation { *Cards::fromString("Js 3d Jd Jh 9d 2s 2c"), FullHouse { CardRank::Jack, CardRank::Two } },
                                   FullHouseExpectation { *Cards::fromString("8s 3d 2d Qh 8d Qs 8c"), FullHouse { CardRank::Eight, CardRank::Queen} },
                                   FullHouseExpectation { *Cards::fromString("Js Jd Kd Kh 9d Ks Jc"), FullHouse { CardRank::King, CardRank::Jack } },
                                   FullHouseExpectation { *Cards::fromString("As Ad 4d Ah 2d 4s 2c"), FullHouse { CardRank::Ace, CardRank::Four } },
                                   FullHouseExpectation { *Cards::fromString("Qs Qd Qc Ts Td 9s 9d"), FullHouse { CardRank::Queen, CardRank::Ten } } );
            auto fullHouse = getFullHouse(cards.mCards);
            REQUIRE(fullHouse);
            CHECK(*fullHouse == cards.mFullHouse);
        }
        SECTION("Negative") {
            auto cards = GENERATE(
                    Cards::fromString("Js Jd Qd Jh 9d 2s 3c"),
                    Cards::fromString("8s 8d 2d 8h 2d 2s 8c"), 
                    Cards::fromString("Js Jd Kd Kh 9d 9s 2c"),
                    Cards::fromString("2s 3d 4d 5h 6d 7s 8c"),
                    Cards::fromString("Js 3s 2s Qs 9s 5s 4s"),
                    Cards::fromString("As 8d 2d Qh 9d 2s 2c")
            );
            CHECK(!getFullHouse(*cards));
        }
    }

    SECTION("Flush") {
        SECTION("Positive") {
            auto cards = GENERATE(
                FlushExpectation { *Cards::fromString("7d 8d Qd 9s Js 2d 5d")
                    , Flush { CardRanks( { CardRank::Seven, CardRank::Eight, CardRank::Queen, CardRank::Two, CardRank::Five} ), Suit::Diamond } }, 
                FlushExpectation { *Cards::fromString("4c 5h Kh Ah Ac 9h Jh")
                    , Flush { CardRanks( { CardRank::Ace, CardRank::King, CardRank::Jack, CardRank::Nine, CardRank::Five }), Suit::Heart } },
                FlushExpectation { *Cards::fromString("2s 3s As Ks 9s Td Th")
                    , Flush { CardRanks( { CardRank::Ace, CardRank::King, CardRank::Nine, CardRank::Three, CardRank::Two }), Suit::Spade } },
                FlushExpectation { *Cards::fromString("3d Jd 6c 7c Qc Kc 8c")
                    , Flush { CardRanks( { CardRank::King, CardRank::Queen, CardRank::Eight, CardRank::Seven, CardRank::Six }), Suit::Clubs } },
                FlushExpectation { *Cards::fromString("2c 3c 7c Tc Jc 4c 9c")
                    , Flush { CardRanks( { CardRank::Ten, CardRank::Jack, CardRank::Nine, CardRank::Seven, CardRank::Four }), Suit::Clubs } }
            );

            auto flush = getFlush(cards.mCards);
            REQUIRE(flush);
            CHECK(*flush == cards.mFlush);
        }
        SECTION("Negative") {
            auto cards = GENERATE(
                    *Cards::fromString("6h 3h 8d 5h 3s 3c Kd"),
                    *Cards::fromString("2d Kd 9d Kh 3d 7c Qc"), 
                    *Cards::fromString("Kd 6s 2c Js Ah 7c As"),
                    *Cards::fromString("8h Kh 4d 2d 5s 3h 3s"),
                    *Cards::fromString("Jd 5c 3c Ks 6d 9d 9s"),
                    *Cards::fromString("Ks 8d Jd 9d 6d 6c Ah")
            );

            CHECK(!getFlush(cards));
        }
    }

    SECTION("Straight") {
        SECTION("Positive") {
            auto cards = GENERATE(
                StraightExpectation { *Cards::fromString("Td Ad Jh 9s Js 8c 7h"), Straight { CardRank::Jack } },
                StraightExpectation { *Cards::fromString("As Kd Qs 2c 3d 4d 5c"), Straight { CardRank::Five } },
                StraightExpectation { *Cards::fromString("7d 5h Qs Jd Kc As Td"), Straight { CardRank::Ace } },
                StraightExpectation { *Cards::fromString("4d 9h 8c 6h 5s 7d Ac"), Straight { CardRank::Nine } },
                StraightExpectation { *Cards::fromString("6h 7h 8d 9c Ts Jc Qh"), Straight { CardRank::Queen } }
            );

            auto straight = getStraight(cards.mCards);
            REQUIRE(straight);
            CHECK(*straight== cards.mStraight);
        }
        SECTION("Negative") {
            auto cards = GENERATE(
                Cards::fromString("Js Jd Qd Jh 9d 2s 3c"),
                Cards::fromString("8s 8d 2d 8h 2d 2s 8c"), 
                Cards::fromString("Js Jd Kd Kh 9d 9s 2c"),
                Cards::fromString("2s 3d 4d 5h 6d 7s 8c"),
                Cards::fromString("Js 3s 2s Qs 9s 5s 4s"),
                Cards::fromString("As 8d 2d Qh 9d 2s 2c")
            );

            CHECK(!getStraight(*cards));
        }
    }

    SECTION("Tripps") {
        SECTION("Positive") {
            auto cards = GENERATE(
                    TrippsExpectation { *Cards::fromString("Js Jd Qd Jh 9d 2s 3c"), Tripps { CardRank::Jack, CardRanks({ CardRank::Queen, CardRank::Nine })} },
                    TrippsExpectation { *Cards::fromString("8s Td 2d 8h 5d 9s 8c"), Tripps { CardRank::Eight, CardRanks({ CardRank::Ten, CardRank::Nine })} },
                    TrippsExpectation { *Cards::fromString("Js Qd Kd Kh Kc 9s 2c"), Tripps { CardRank::King, CardRanks({ CardRank::Queen, CardRank::Jack})} },
                    TrippsExpectation { *Cards::fromString("2s 3d 4d 5h 6d 6s 6c"), Tripps { CardRank::Six, CardRanks({ CardRank::Four, CardRank::Five})} }
            );

            auto tripps = getTripps(cards.mCards);
            REQUIRE(tripps);
            CHECK(*tripps == cards.mTripps);
        }
        SECTION("Negative") {
            auto cards = GENERATE(
                    *Cards::fromString("6h 3h 8d 5h 3s 9c Kd"),
                    *Cards::fromString("2d Kd 9d Kh 3d 7c Qc"), 
                    *Cards::fromString("Kd 6s 2c Js Ah 7c As"),
                    *Cards::fromString("8h Kh 4d 2d 5s 3h 3s"),
                    *Cards::fromString("Jd 5c 3c Ks 6d 9d 9s"),
                    *Cards::fromString("Ks 8d Jd 9d 6d 6c Ah")
            );
            CHECK(!getTripps(cards));
        }
    }

    SECTION("Two pair") {
        SECTION("Positive") {

        }
        SECTION("Negative") {

        }
    }

    SECTION("One pair") {
        SECTION("Positive") {

        }
        SECTION("Negative") {

        }
    }

    SECTION("High card") {

    }
}