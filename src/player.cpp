#include "player.hpp"

#include <sstream>

namespace professor
{
std::string Player::toString() const 
{
    std::ostringstream oss;
    oss << mName << "(" << mChips << ")";
    if(mCards) {
        oss << ": " << mCards->toString();
    }
    return oss.str();
}
}