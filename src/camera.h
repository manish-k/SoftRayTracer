#pragma once

#include "image.h"
#include "geometry/vector.h"
#include "geometry/ray.h"
#include "world.h"

class Camera
{
public:
    Camera(Vec3f position, float aspect_ratio, int width);
    ~Camera() = default;

    void update(float aspect_ratio, int width);
    void render(Image* img, World& world);

private:
    Color get_bg_color(const Ray& r);

private:
    int   m_image_width  = 0;
    int   m_image_height = 0;
    float m_aspect_ratio = 0.f;
    Vec3f m_position     = Vec3f {};

    // viewport
    Vec3f m_vp_origin       = Vec3f {};
    Vec3f m_vp_axis_u       = Vec3f {};
    Vec3f m_vp_axis_v       = Vec3f {};
    Vec3f m_vp_pixel_step_u = Vec3f {};
    Vec3f m_vp_pixel_step_v = Vec3f {};
};