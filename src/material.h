#pragma once

#include "geometry/traceable.h"
#include "color.h"
#include "math/tmath.h"

struct ShadingInfo
{
    Color              attenuation;
    std::optional<Ray> scatterd;
};

class Material
{
public:
    virtual ~Material() = default;

    virtual ShadingInfo scatter(
        const Ray&           in_ray,
        const IntersectInfo& intersect_info,
        uint32_t             seed) const
        = 0;
};

class Lambertian : public Material
{
public:
    Lambertian(const Color& albedo) :
        m_albedo(albedo) {};

    ShadingInfo scatter(
        const Ray&           in_ray,
        const IntersectInfo& intersect_info,
        uint32_t             seed) const override
    {
        Vec3f scattered_direction = (intersect_info.normal + rand_unit_vector(seed));

        if (scattered_direction.near_zero())
            scattered_direction = intersect_info.normal;

        scattered_direction.normaliize();

        return {
            m_albedo,
            Ray { intersect_info.point, scattered_direction }
        };
    }

private:
    Color m_albedo {};
};

class Metal : public Material
{
public:
    Metal(const Color& albedo, float fuzz) :
        m_albedo(albedo), m_fuzz(fuzz < 1.f ? fuzz : 1) {};

    ShadingInfo scatter(
        const Ray&           in_ray,
        const IntersectInfo& intersect_info,
        uint32_t             seed) const override
    {
        Vec3f reflected_direction = reflect(in_ray.direction, intersect_info.normal).normaliize();
        reflected_direction = reflected_direction + (m_fuzz * rand_unit_vector(seed));

        return {
            m_albedo,
            Ray { intersect_info.point, reflected_direction }
        };
    }

private:
    Color m_albedo {};
    float m_fuzz {};
};