#pragma once
#include <ostream>
#include "hand_value.hpp"

namespace std 
{
std::ostream& operator << ( std::ostream& os, professor::IHandValueType const& value );
std::ostream& operator << ( std::ostream& os, professor::HighCard const& value );
std::ostream& operator << ( std::ostream& os, professor::OnePair const& value );
std::ostream& operator << ( std::ostream& os, professor::TwoPair const& value );
std::ostream& operator << ( std::ostream& os, professor::Tripps const& value );
std::ostream& operator << ( std::ostream& os, professor::Straight const& value );
std::ostream& operator << ( std::ostream& os, professor::Flush const& value );
std::ostream& operator << ( std::ostream& os, professor::FullHouse const& value );
std::ostream& operator << ( std::ostream& os, professor::Quads const& value );
std::ostream& operator << ( std::ostream& os, professor::StraightFlush const& value );
std::ostream& operator << ( std::ostream& os, professor::RoyalFlush const& value );
}