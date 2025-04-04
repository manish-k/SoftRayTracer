#pragma once

#include "geometry/traceable.h"
#include "geometry/sphere.h"
#include "utils/log.h"

#include <vector>
#include <memory>

struct World : public Traceable
{
    std::vector<std::shared_ptr<Traceable>> traceable_objects {};

    World() = default;
    World(size_t world_size) { traceable_objects.resize(world_size); };
    ~World() = default;

    void add(std::shared_ptr<Traceable> object)
    {
        traceable_objects.push_back(object);
    }

    void clear()
    {
        traceable_objects.clear();
    }

    std::optional<IntersectInfo> intersect(
        const Ray& r, float ray_t_min, float ray_t_max) const override
    {
        std::optional<IntersectInfo> intersect_info {};
        for (auto& obj : traceable_objects)
        {
            std::optional<IntersectInfo> obj_intersect_info = obj->intersect(r, ray_t_min, ray_t_max);
            if (obj_intersect_info)
            {
                ray_t_max      = (*obj_intersect_info).t;
                intersect_info = obj_intersect_info;
            }
        }

        return intersect_info;
    }
};