#pragma once

#include "vector.h"
#include "traceable.h"
#include "utils/log.h"
#include "material.h"

#include <memory>

class Sphere : public Traceable
{
public:
    Sphere(const Vec3f& center, float radius, std::shared_ptr<Material> mat) :
        m_center(center), m_radius(radius), m_material(mat) {};

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
        Vec3f out_normal         = (intersection_point - m_center) / m_radius;
        bool  front_face         = (out_normal * r.direction) < 0;

        out_normal = front_face ? out_normal : -1 * out_normal;

        return IntersectInfo {
            intersection_point,
            out_normal,
            nearest_root_t,
            front_face,
            m_material
        };
    }

private:
    Vec3f                     m_center {};
    float                     m_radius {};
    std::shared_ptr<Material> m_material = nullptr;
};