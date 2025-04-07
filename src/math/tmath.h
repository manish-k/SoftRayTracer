#pragma once

#include <chrono>
#include <limits>

static constexpr float Inf = std::numeric_limits<double>::infinity();

// src: https://iquilezles.org/articles/sfrand/
inline float frand(int* seed)
{
    union
    {
        float        fres;
        unsigned int ires;
    };

    *seed = 0x00269ec3 + (*seed) * 0x000343fd;
    ires  = ((((unsigned int)*seed) >> 9) | 0x3f800000);
    return fres - 1.0f;
}

inline float time_now()
{
    auto time_since_epoch = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
    return static_cast<float>(time_since_epoch) / 1e9;
}

inline constexpr uint32_t get_static_seed()
{
    return 44563123;
}

// src: https://www.reedbeta.com/blog/hash-functions-for-gpu-rendering/
inline uint32_t pcg_hash(uint32_t input)
{
    uint32_t state = input * 747796405u + 2891336453u;
    uint32_t word  = ((state >> ((state >> 28u) + 4u)) ^ state) * 277803737u;
    return (word >> 22u) ^ word;
}

inline float rand_float(uint32_t& seed)
{
    seed = pcg_hash(seed);
    return (float)seed / (float)UINT32_MAX;
}