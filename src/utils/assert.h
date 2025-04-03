#pragma once

#include "log.h"

#ifdef NDEBUG
#    define ASSERT(...)
#else
#    define ASSERT(check, ...)           \
        {                                \
            if (!(check))                \
            {                            \
                log_assert(__VA_ARGS__); \
                __debugbreak();          \
            }                            \
        }
#endif