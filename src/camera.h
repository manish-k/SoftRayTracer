#pragma once

#include "image.h"
#include "geometry/vector.h"
#include "geometry/ray.h"
#include "world.h"
#include "math/tmath.h"

class Camera
{
public:
    Camera(Vec3f position, float aspect_ratio, float fov, int width);
    ~Camera() = default;

    void update(float aspect_ratio, float fov);
    void set_view_direction(Vec3f position, Vec3f look_at_dir, Vec3f up);
    void set_view_target(Vec3f position, Vec3f target, Vec3f up);
    void render(Image* img, World& world);

private:
    void  update_vp_axes();
    Color get_bg_color(const Ray& r);
    Color get_ray_color(const Ray& r, World& world, uint32_t max_bounces);

private:
    int   m_image_width  = 0;
    int   m_image_height = 0;
    float m_aspect_ratio = 0.f;
    Vec3f m_position     = Vec3f {};
    float m_fov          = 90.f;

    float m_lens_fov          = 0.f;
    float m_lens_focal_length = 10.f;
    float m_lens_radius       = 0.f;
    Vec3f m_lens_u            = Vec3f(1.f, 0.f, 0.f);
    Vec3f m_lens_v            = Vec3f(0.f, 1.f, 0.f);

    // camera's basis vectors
    Vec3f m_u = Vec3f(1.f, 0.f, 0.f);
    Vec3f m_v = Vec3f(0.f, 1.f, 0.f);
    Vec3f m_w = Vec3f(0.f, 0.f, 1.f); // opposite of view direction bcos rhs

    // viewport
    Vec3f    m_vp_origin       = Vec3f {};
    float    m_vp_width        = 0.f;
    float    m_vp_height       = 0.f;
    Vec3f    m_vp_pixel_step_u = Vec3f {};
    Vec3f    m_vp_pixel_step_v = Vec3f {};

    uint32_t m_seed                 = get_static_seed();
    uint32_t m_aa_samples_per_pixel = 500;

    uint32_t m_max_ray_bounces = 50;
};