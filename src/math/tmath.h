#pragma once

#include "geometry/vector.h"

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

// generate random float in [0, 1)
inline float rand_float(uint32_t& seed)
{
    seed = pcg_hash(seed);
    return (float)seed / (float)UINT32_MAX;
}

inline float rand_float(uint32_t& seed, int min, int max)
{
    return min + (max - min) * rand_float(seed);
}

inline Vec3f rand_vector(uint32_t& seed)
{
    return Vec3f(rand_float(seed, -1, 1), rand_float(seed, -1, 1), rand_float(seed, -1, 1));
}

inline Vec3f rand_unit_vector(uint32_t& seed)
{
    Vec3f vec = rand_vector(seed);

    if (vec.squared_magnitude() - std::numeric_limits<float>::epsilon() <= 0.0f)
    {
        vec = rand_vector(seed);
    }

    return vec.normaliize();
}