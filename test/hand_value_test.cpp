#include "catch.hpp"
#include "utility/debug.hpp"
#include "base/hand_value.hpp"

using namespace professor;

struct RoyalFlushExpectation {
    Cards mCards;
    RoyalFlush mRoyalFlush;
};

struct StraightFlushExpectation {
    Cards mCards;
    StraightFlush mStraightFlush;
};

struct QuadsExpectation {
    Cards mCards;
    Quads mQuads;
};
struct FullHouseExpectation {
    Cards mCards;
    FullHouse mFullHouse;
};

struct FlushExpectation {
    Cards mCards;
    Flush mFlush;
};

struct StraightExpectation {
    Cards mCards;
    Straight mStraight;
};

struct TrippsExpectation {
    Cards mCards;
    Tripps mTripps;
};

struct TwoPairExpecatation {
    Cards mCards;
    TwoPair mTwoPair;
};

struct OnePairExpectation {
    Cards mCards;
    OnePair mOnePair;
};

struct HighCardExpectation {
    Cards mCards;
    HighCard mHighCard;
};

TEST_CASE("Hand value test")
{
    SECTION("Royal flushes")
    {
        SECTION("Positive")
        {
            auto cards = GENERATE(
                RoyalFlushExpectation { *Cards::fromString("2d Kd Ad Td Qd 3h Jd"), RoyalFlush { Suit::Diamond } },
                RoyalFlushExpectation { *Cards::fromString("Ah 9h Th Qh Kh 8d Jh"), RoyalFlush { Suit::Heart } },
                RoyalFlushExpectation { *Cards::fromString("Tc Jc Qc Kc Ac 9h 2d"), RoyalFlush { Suit::Clubs } },
                RoyalFlushExpectation { *Cards::fromString("5d 6h Ks Js Qs As Ts"), RoyalFlush { Suit::Spade } });

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
                *Cards::fromString("Th 8s 8c 5d Ts Jc 6s"));

            CHECK(!getRoyalFlush(cards));
        }
    }

    SECTION("Straight flushes")
    {
        SECTION("Positive")
        {
            auto cards = GENERATE(
                StraightFlushExpectation { *Cards::fromString("As 2s 3s 4s 5s 9d Kd"), StraightFlush { CardRank::Five, Suit::Spade } },
                StraightFlushExpectation { *Cards::fromString("4d 5d 6d 7d 8d Kh Ac"), StraightFlush { CardRank::Eight, Suit::Diamond } },
                StraightFlushExpectation { *Cards::fromString("6h 7h 8h 9h Th Jh Qh"), StraightFlush { CardRank::Queen, Suit::Heart } },
                StraightFlushExpectation { *Cards::fromString("Kc Qc Jc Tc 9c 2d 3h"), StraightFlush { CardRank::King, Suit::Clubs } });

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
                *Cards::fromString("Ah Kh Qh Jh Th 3d 8d"));
            CHECK(!getStraightFlush(cards));
        }
    }

    SECTION("Quads")
    {
        SECTION("Positive")
        {
            auto cards = GENERATE(
                QuadsExpectation { *Cards::fromString("As Ad Jc Ah Kd 2s Ac"), Quads { CardRank::Ace, CardRank::King } },
                QuadsExpectation { *Cards::fromString("Js 3d 2d 2h 9d 2s 2c"), Quads { CardRank::Two, CardRank::Jack } });
            auto quads = getQuads(cards.mCards);
            REQUIRE(quads);
            CHECK(*quads == cards.mQuads);
        }

        SECTION("Negative")
        {
            auto cards = GENERATE(Cards::fromString("Js 3d 2d Qh 9d 2s 2c"),
                Cards::fromString("8s 3d 2d Qh 7d As 2c"),
                Cards::fromString("Js Jd Kd Kh 9d Ks Jc"),
                Cards::fromString("2s 3d 4d 5h 6d 7s 8c"),
                Cards::fromString("Js 3s 2s Qs 9s 5s 4s"),
                Cards::fromString("As 8d 2d Qh 9d 2s 2c"));
            CHECK(!getQuads(*cards));
        }
    }

    SECTION("Full house")
    {
        SECTION("Positive")
        {
            auto cards = GENERATE(FullHouseExpectation { *Cards::fromString("Js 3d Jd Jh 9d 2s 2c"), FullHouse { CardRank::Jack, CardRank::Two } },
                FullHouseExpectation { *Cards::fromString("8s 3d 2d Qh 8d Qs 8c"), FullHouse { CardRank::Eight, CardRank::Queen } },
                FullHouseExpectation { *Cards::fromString("Js Jd Kd Kh 9d Ks Jc"), FullHouse { CardRank::King, CardRank::Jack } },
                FullHouseExpectation { *Cards::fromString("As Ad 4d Ah 2d 4s 2c"), FullHouse { CardRank::Ace, CardRank::Four } },
                FullHouseExpectation { *Cards::fromString("Qs Qd Qc Ts Td 9s 9d"), FullHouse { CardRank::Queen, CardRank::Ten } });
            auto fullHouse = getFullHouse(cards.mCards);
            REQUIRE(fullHouse);
            CHECK(*fullHouse == cards.mFullHouse);
        }
        SECTION("Negative")
        {
            auto cards = GENERATE(
                Cards::fromString("Js Jd Qd Jh 9d 2s 3c"),
                Cards::fromString("Js Jd Kd Kh 9d 9s 2c"),
                Cards::fromString("2s 3d 4d 5h 6d 7s 8c"),
                Cards::fromString("Js 3s 2s Qs 9s 5s 4s"),
                Cards::fromString("As 8d 2d Qh 9d 2s 2c"));
            CHECK(!getFullHouse(*cards));
        }
    }

    SECTION("Flush")
    {
        SECTION("Positive")
        {
            auto cards = GENERATE(
                FlushExpectation { *Cards::fromString("7d 8d Qd 9s Js 2d 5d"), Flush { CardRanks({ CardRank::Seven, CardRank::Eight, CardRank::Queen, CardRank::Two, CardRank::Five }), Suit::Diamond } },
                FlushExpectation { *Cards::fromString("4c 5h Kh Ah Ac 9h Jh"), Flush { CardRanks({ CardRank::Ace, CardRank::King, CardRank::Jack, CardRank::Nine, CardRank::Five }), Suit::Heart } },
                FlushExpectation { *Cards::fromString("2s 3s As Ks 9s Td Th"), Flush { CardRanks({ CardRank::Ace, CardRank::King, CardRank::Nine, CardRank::Three, CardRank::Two }), Suit::Spade } },
                FlushExpectation { *Cards::fromString("3d Jd 6c 7c Qc Kc 8c"), Flush { CardRanks({ CardRank::King, CardRank::Queen, CardRank::Eight, CardRank::Seven, CardRank::Six }), Suit::Clubs } },
                FlushExpectation { *Cards::fromString("2c 3c 7c Tc Jc 4c 9c"), Flush { CardRanks({ CardRank::Ten, CardRank::Jack, CardRank::Nine, CardRank::Seven, CardRank::Four }), Suit::Clubs } });

            auto flush = getFlush(cards.mCards);
            REQUIRE(flush);
            CHECK(*flush == cards.mFlush);
        }
        SECTION("Negative")
        {
            auto cards = GENERATE(
                *Cards::fromString("6h 3h 8d 5h 3s 3c Kd"),
                *Cards::fromString("2d Kd 9d Kh 3d 7c Qc"),
                *Cards::fromString("Kd 6s 2c Js Ah 7c As"),
                *Cards::fromString("8h Kh 4d 2d 5s 3h 3s"),
                *Cards::fromString("Jd 5c 3c Ks 6d 9d 9s"),
                *Cards::fromString("Ks 8d Jd 9d 6d 6c Ah"));

            CHECK(!getFlush(cards));
        }
    }

    SECTION("Straight")
    {
        SECTION("Positive")
        {
            auto cards = GENERATE(
                StraightExpectation { *Cards::fromString("Td Ad Jh 9s Js 8c 7h"), Straight { CardRank::Jack } },
                StraightExpectation { *Cards::fromString("As Kd Qs 2c 3d 4d 5c"), Straight { CardRank::Five } },
                StraightExpectation { *Cards::fromString("7d 5h Qs Jd Kc As Td"), Straight { CardRank::Ace } },
                StraightExpectation { *Cards::fromString("4d 9h 8c 6h 5s 7d Ac"), Straight { CardRank::Nine } },
                StraightExpectation { *Cards::fromString("6h 7h 8d 9c Ts Jc Qh"), Straight { CardRank::Queen } });

            auto straight = getStraight(cards.mCards);
            REQUIRE(straight);
            CHECK(*straight == cards.mStraight);
        }
        SECTION("Negative")
        {
            auto cards = GENERATE(
                Cards::fromString("Js Jd Qd Jh 9d 2s 3c"),
                Cards::fromString("8s 8d 2d 8h 2c 2s 8c"),
                Cards::fromString("Js Jd Kd Kh 9d 9s 2c"),
                Cards::fromString("2s Qd 4d 5h Ad 7s 8c"),
                Cards::fromString("Js 3s 2s Qs 9s 5s 4s"),
                Cards::fromString("As 8d 2d Qh 9d 2s 2c"));

            CHECK(!getStraight(*cards));
        }
    }

    SECTION("Tripps")
    {
        SECTION("Positive")
        {
            auto cards = GENERATE(
                TrippsExpectation { *Cards::fromString("Js Jd Qd Jh 9d 2s 3c"), Tripps { CardRank::Jack, CardRanks({ CardRank::Queen, CardRank::Nine }) } },
                TrippsExpectation { *Cards::fromString("8s Td 2d 8h 5d 9s 8c"), Tripps { CardRank::Eight, CardRanks({ CardRank::Ten, CardRank::Nine }) } },
                TrippsExpectation { *Cards::fromString("Js Qd Kd Kh Kc 9s 2c"), Tripps { CardRank::King, CardRanks({ CardRank::Queen, CardRank::Jack }) } },
                TrippsExpectation { *Cards::fromString("2s 3d 4d 5h 6d 6s 6c"), Tripps { CardRank::Six, CardRanks({ CardRank::Four, CardRank::Five }) } });

            auto tripps = getTripps(cards.mCards);
            REQUIRE(tripps);
            CHECK(*tripps == cards.mTripps);
        }
        SECTION("Negative")
        {
            auto cards = GENERATE(
                *Cards::fromString("6h 3h 8d 5h 3s 9c Kd"),
                *Cards::fromString("2d Kd 9d Kh 3d 7c Qc"),
                *Cards::fromString("Kd 6s 2c Js Ah 7c As"),
                *Cards::fromString("8h Kh 4d 2d 5s 3h 3s"),
                *Cards::fromString("Jd 5c 3c Ks 6d 9d 9s"),
                *Cards::fromString("Ks 8d Jd 9d 6d 6c Ah"));
            CHECK(!getTripps(cards));
        }
    }

    SECTION("Two pair")
    {
        SECTION("Positive")
        {
            auto cards = GENERATE(
                TwoPairExpecatation { *Cards::fromString("3s Ts Ac Js Tc 3d 8h"), TwoPair { CardRank::Ten, CardRank::Three, CardRank::Ace } },
                TwoPairExpecatation { *Cards::fromString("6c 6h Jd 2d 5h 8h 8c"), TwoPair { CardRank::Eight, CardRank::Six, CardRank::Jack } },
                TwoPairExpecatation { *Cards::fromString("Ac Ah Kd Ks Qh Qd Jh"), TwoPair { CardRank::Ace, CardRank::King, CardRank::Queen } });

            auto twoPair = getTwoPair(cards.mCards);
            REQUIRE(twoPair);
            CHECK(*twoPair == cards.mTwoPair);
        }
        SECTION("Negative")
        {
            auto cards = GENERATE(
                *Cards::fromString("6h 3h 8d 5h 3s 9c Kd"),
                *Cards::fromString("2d Kd 9d Kh 3d 7c Qc"),
                *Cards::fromString("Kd 6s 2c Js Ah 7c As"),
                *Cards::fromString("8h Kh 4d 2d 5s 3h 3s"),
                *Cards::fromString("Jd 5c 3c Ks 6d 9d 9s"),
                *Cards::fromString("Ks 8d Jd 9d 6d 6c Ah"));
            CHECK(!getTwoPair(cards));
        }
    }

    SECTION("One pair")
    {
        SECTION("Positive")
        {
            auto cards = GENERATE(
                OnePairExpectation { *Cards::fromString("8h 8d Kc Qc 4d Jc 2s"), OnePair { CardRank::Eight, CardRanks({ CardRank::King, CardRank::Queen, CardRank::Jack }) } },
                OnePairExpectation { *Cards::fromString("5s Ad 7h As 3h 4s Th"), OnePair { CardRank::Ace, CardRanks({ CardRank::Ten, CardRank::Seven, CardRank::Five }) } },
                OnePairExpectation { *Cards::fromString("Ad Qs 3d 2h Ts 7s 3h"), OnePair { CardRank::Three, CardRanks({ CardRank::Ace, CardRank::Queen, CardRank::Ten }) } });

            auto onePair = getOnePair(cards.mCards);
            REQUIRE(onePair);
            CHECK(*onePair == cards.mOnePair);
        }
        SECTION("Negative")
        {
            auto cards = GENERATE(
                *Cards::fromString("6h 3h 8d 5h 9s Jc Kd"),
                *Cards::fromString("2d Kd 9d Qh 3d 7c 4c"),
                *Cards::fromString("Kd 6s 2c Js Ah 7c 8s"),
                *Cards::fromString("8h Kh 4d 2d 5s Ah 3s"),
                *Cards::fromString("Ks 8d Jd 9d 6d 7c Ah"));

            CHECK(!getOnePair(cards));
        }
    }

    SECTION("High card")
    {
        auto cards = GENERATE(
            HighCardExpectation { *Cards::fromString("6h 3h 8d 5h 9s Jc Kd"), HighCard { CardRanks({ CardRank::King, CardRank::Jack, CardRank::Nine, CardRank::Eight, CardRank::Six }) } },
            HighCardExpectation { *Cards::fromString("2d Kd 9d Qh 3d 7c 4c"), HighCard { CardRanks({ CardRank::King, CardRank::Queen, CardRank::Nine, CardRank::Seven, CardRank::Four }) } },
            HighCardExpectation { *Cards::fromString("Kd 6s 2c Js Ah 7c 8s"), HighCard { CardRanks({ CardRank::Ace, CardRank::King, CardRank::Jack, CardRank::Eight, CardRank::Seven }) } });
        auto highCard = getHighCard(cards.mCards);
        REQUIRE(highCard);
        CHECK(*highCard == cards.mHighCard);
    }

    SECTION("Comparison")
    {
        auto playerOneCards = *Cards::fromString("2h Ad 6h 3c 5c 8c 6d");
        auto playerTwoCards = *Cards::fromString("Ah Jc 6h 3c 5c 8c 6d");
        HandValue playerOneHandValue(playerOneCards);
        HandValue playerTwoHandValue(playerTwoCards);
        CHECK(playerTwoHandValue.getHandValueType() > playerOneHandValue.getHandValueType());
    }
}
