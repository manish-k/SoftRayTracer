#pragma once

#include "vector.h"
#include "utils/tassert.h"

struct Ray
{
    Vec3f origin;
    Vec3f direction;

    Ray(const Vec3f& origin, const Vec3f& direction) :
        origin(origin), direction(direction) {};
    Ray() :
        origin(Vec3f {}), direction(Vec3f {}) {};

    Vec3f at(float t) const
    {
        ASSERT(t >= 0, "t should not be negative");
        return origin + t * direction;
    }
};
