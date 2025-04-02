#pragma once

#include "vector.h"

struct Ray
{
    Vec3f origin;
    Vec3f direction;

    Ray(const Vec3f& origin, const Vec3f& direction) :
        origin(origin), direction(direction) {};

    Vec3f at(float t) const
    {
        // TODO: t should be non negative
        return origin + t * direction;
    }
};
