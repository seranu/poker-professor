#pragma once
#include <stdio.h>
#include <string>
#include <chrono>

#ifndef NDEBUG
#define PP_LOG_DEBUG(...) PP_LOG(__VA_ARGS__)
#define PP_LOG_INFO(...) PP_LOG(__VA_ARGS__)
#else
#define PP_LOG_DEBUG(...)
#define PP_LOG_INFO(...) PP_LOG(__VA_ARGS__)
#endif

#define PP_LOG(fmt, ...) do { fprintf(stderr, fmt "\n", ## __VA_ARGS__); } while(0)

namespace professor {
class ScopeTimer
{
public:
    ScopeTimer(const char * name);
    ~ScopeTimer();
private:
    std::string mName;
    std::chrono::time_point<std::chrono::high_resolution_clock> mStart;
};
}

#define SCOPE_TIMER(name) professor::ScopeTimer _scopeTimer(name)