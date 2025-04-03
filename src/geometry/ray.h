#pragma once

#include "vector.h"
#include "utils/assert.h"

struct Ray
{
    Vec3f origin;
    Vec3f direction;

    Ray(const Vec3f& origin, const Vec3f& direction) :
        origin(origin), direction(direction) {};

    Vec3f at(float t) const
    {
        ASSERT(t >= 0, "t should not be negative");
        return origin + t * direction;
    }
};
