#pragma once
#include <stdio.h>

#ifndef NDEBUG
#define PP_LOG_DEBUG(...) PP_LOG(__VA_ARGS__)
#else
#define PP_LOG_DEBUG(...)
#endif

#define PP_LOG_INFO(...) PP_LOG(__VA_ARGS__)

#define PP_LOG(fmt, ...) do { fprintf(stderr, "%s:%d " fmt "\n", __FILE__, __LINE__, ## __VA_ARGS__); } while(0)
