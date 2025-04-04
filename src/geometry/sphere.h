#pragma once

#include "vector.h"
#include "traceable.h"
#include "utils/log.h"

class Sphere : public Traceable
{
public:
    Sphere(const Vec3f& center, float radius) :
        m_center(center), m_radius(radius) {};

    std::optional<IntersectInfo> intersect(
        const Ray& r, float ray_t_min, float ray_t_max) const override
    {
        // using equations from https://raytracing.github.io/books/RayTracingInOneWeekend.html#surfacenormalsandmultipleobjects/simplifyingtheray-sphereintersectioncode

        Vec3f oc = m_center - r.origin;
        float a  = r.direction.squared_magnitude();
        float h  = r.direction * oc;
        float c  = oc.squared_magnitude() - m_radius * m_radius;
        
        float discriminant = h * h - a * c;

        if (discriminant < 0) // no intersection
            return {};

        // taking -ive from +/- root because it is nearest to ray origin
        float nearest_root_t = (h - std::sqrt(discriminant)) / a; 

        if (nearest_root_t >= ray_t_max || nearest_root_t <= ray_t_min)
        {
            // check the other root
            nearest_root_t = (h + std::sqrt(discriminant)) / a; 

            if (nearest_root_t >= ray_t_max || nearest_root_t <= ray_t_min)
            {
                // no root found in range
                return {};
            }
        }

        Vec3f intersection_point = r.at(nearest_root_t);

        return IntersectInfo
        {
            intersection_point,
                (intersection_point - m_center) / m_radius,
                false
        };
    }

private:
    Vec3f m_center;
    float m_radius;
};