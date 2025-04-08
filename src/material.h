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
        uint32_t&            seed) const
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
        uint32_t&            seed) const override
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
        uint32_t&            seed) const override
    {
        Vec3f reflected_direction = reflect(in_ray.direction, intersect_info.normal).normaliize();
        reflected_direction       = reflected_direction + (m_fuzz * rand_unit_vector(seed));

        return {
            m_albedo,
            Ray { intersect_info.point, reflected_direction }
        };
    }

private:
    Color m_albedo {};
    float m_fuzz {};
};

class Dielectric : public Material
{
public:
    Dielectric(float refraction_index) :
        m_refractive_index(refraction_index)
    {
        m_r0 = (1 - refraction_index) / (1 + refraction_index);
        m_r0 = m_r0 * m_r0;
    };

    ShadingInfo scatter(
        const Ray&           in_ray,
        const IntersectInfo& intersect_info,
        uint32_t&            seed) const override
    {
        float relative_ri = intersect_info.front_face ? (1.0f / m_refractive_index) : m_refractive_index;

        Vec3f incident_unit_direction = in_ray.direction.unit_vector();

        float cosine_incidence = std::fmin((-1.f * incident_unit_direction) * intersect_info.normal, 1.f);
        float sine_incidence   = std::sqrt(1.f - cosine_incidence * cosine_incidence);

        Vec3f scatterd_direction;

        if (relative_ri * sine_incidence > 1.f || reflectance(cosine_incidence) > rand_float(seed))
        {
            // reflection;
            scatterd_direction = reflect(incident_unit_direction, intersect_info.normal);
        }
        else
        {
            scatterd_direction = refract(
                incident_unit_direction,
                intersect_info.normal,
                relative_ri);
            // refraction
        }

        return {
            Color(1.f, 1.f, 1.f),
            Ray { intersect_info.point, scatterd_direction }
        };
    }

private:
    float reflectance(float cosine) const
    {
        // Use Schlick's approximation for reflectance.
        return m_r0 + (1.f - m_r0) * std::pow((1.f - cosine), 5);
    }

private:
    float m_refractive_index {}; // relative to incidence ray medium
    float m_r0 {};               // Schlick's approximation precalculated constant
};