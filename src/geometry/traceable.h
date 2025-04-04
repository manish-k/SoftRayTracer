#pragma once

#include "vector.h"
#include "ray.h"

#include <optional>

struct IntersectInfo
{
    Vec3f point;
    Vec3f normal;
    float t;
    bool  front_face;
};

class Traceable
{
public:
    virtual ~Traceable() = default;

    virtual std::optional<IntersectInfo> intersect(const Ray& r, float ray_t_min, float ray_t_max) const = 0;
};