#include "debug.hpp"

namespace {
template<typename T>
std::ostream& localToString(std::ostream& os, T const & value)
{
    os << value.toString();
    return os;
}
}
namespace std
{
std::ostream& operator << ( std::ostream& os, professor::HighCard const& value )
{
    return localToString(os, value);
}

std::ostream& operator << ( std::ostream& os, professor::OnePair const& value )
{
    return localToString(os, value);
}

std::ostream& operator << ( std::ostream& os, professor::TwoPair const& value )
{
    return localToString(os, value);
}

std::ostream& operator << ( std::ostream& os, professor::Tripps const& value )
{
    return localToString(os, value);
}

std::ostream& operator << ( std::ostream& os, professor::Straight const& value )
{
    return localToString(os, value);
}

std::ostream& operator << ( std::ostream& os, professor::Flush const& value )
{
    return localToString(os, value);
}

std::ostream& operator << ( std::ostream& os, professor::FullHouse const& value )
{
    return localToString(os, value);
}

std::ostream& operator << ( std::ostream& os, professor::Quads const& value )
{
    return localToString(os, value);
}

std::ostream& operator << ( std::ostream& os, professor::StraightFlush const& value )
{
    return localToString(os, value);
}

std::ostream& operator << ( std::ostream& os, professor::RoyalFlush const& value )
{
    return localToString(os, value);
}
}