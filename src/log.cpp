#include "log.hpp"

namespace professor
{
ScopeTimer::ScopeTimer(const char * name)
    : mName(name)
    , mStart(std::chrono::high_resolution_clock::now())
    {}

ScopeTimer::~ScopeTimer()
{
    auto duration = std::chrono::high_resolution_clock::now() - mStart;
    PP_LOG_INFO("Timer %s took %zums", mName.c_str(), std::chrono::duration_cast<std::chrono::milliseconds>(duration).count());
}
}