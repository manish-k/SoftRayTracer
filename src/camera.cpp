#include "camera.h"
#include "color.h"
#include "utils/log.h"
#include "math/tmath.h"

Camera::Camera(Vec3f position, float aspect_ratio, float fov, int width)
{
    m_position    = position;
    m_fov         = fov;
    m_image_width = width;
    update(aspect_ratio, width);
}

void Camera::update(float aspect_ratio, float fov)
{
    m_image_height = int(m_image_width / aspect_ratio);

    m_image_height = (m_image_height < 1) ? 1 : m_image_height;

    float fov_angle = to_radians(m_fov);
    float h         = tan(fov_angle / 2.f);

    m_vp_height = 2.0f * h * m_focal_length;
    m_vp_width  = m_vp_height * (float(m_image_width) / m_image_height);

    update_vp_axes();
}

void Camera::set_view_direction(Vec3f position, Vec3f look_at_dir, Vec3f up)
{
    m_position = position;

    m_w = look_at_dir.unit_vector();
    m_u = (up.unit_vector() ^ m_w).unit_vector();
    m_v = m_w ^ m_u;

    update_vp_axes();
}

void Camera::set_view_target(Vec3f position, Vec3f target, Vec3f up)
{
    set_view_direction(position, position - target, up);
}

void Camera::render(Image* img, World& world)
{
    Vec3f vp_start_pixel = m_vp_origin + 0.5 * (m_vp_pixel_step_u + m_vp_pixel_step_v);

    float sampling_frequency = 1.f / m_aa_samples_per_pixel;

    for (int j = 0; j < m_image_height; ++j)
    {
        for (int i = 0; i < m_image_width; ++i)
        {
            Color sampled_color;
            Vec2f offsets;

            for (uint32_t sample = 0u; sample < m_aa_samples_per_pixel; ++sample)
            {
                Vec3f pixel_sample = vp_start_pixel + (i + offsets.x) * m_vp_pixel_step_u + (j + offsets.y) * m_vp_pixel_step_v;

                Vec3f ray_direction = pixel_sample - m_position;

                // create ray
                Ray sampled_ray(m_position, ray_direction);

                sampled_color = sampled_color + get_ray_color(sampled_ray, world, m_max_ray_bounces);

                // for 1st sample use the 0,0 offset, useful if sample size is only 1
                // i.e. no anti-aliasing
                offsets = Vec2f(rand_float(m_seed) - 0.5f, rand_float(m_seed) - 0.5f);
            }

            // set color in img
            set_image_pixel_color(img, i, j, sampled_color * sampling_frequency);
        }
    }
}

void Camera::update_vp_axes()
{
    Vec3f vp_u = m_vp_width * m_u;
    Vec3f vp_v = m_vp_height * m_v;

    m_vp_pixel_step_u = vp_u / m_image_width;
    m_vp_pixel_step_v = vp_v / m_image_height;

    m_vp_origin = m_position - (m_focal_length * m_w) - vp_v / 2 - vp_u / 2;
}

Color Camera::get_bg_color(const Ray& r)
{
    Vec3f dir = r.direction.unit_vector();

    float y_clamp = 0.5f * (dir.y + 1.0f); // between 0 to 1

    return (1.f - y_clamp) * Color(1.f, 1.f, 1.f) + y_clamp * Color(0.5f, 0.7f, 1.f);
}

Color Camera::get_ray_color(const Ray& r, World& world, uint32_t max_bounces)
{
    if (max_bounces <= 0)
        return Color(0.f, 0.f, 0.f);

    auto intersect_info = world.intersect(r, 0.001f, Inf);
    if (intersect_info)
    {
        auto&       info      = (*intersect_info);
        Vec3f       ray_start = info.point;
        Material&   mat       = *(info.material);

        ShadingInfo shade_info = mat.scatter(r, info, m_seed);

        if (shade_info.scatterd)
        {
            auto& scattered_ray = *shade_info.scatterd;
            return shade_info.attenuation * get_ray_color(scattered_ray, world, max_bounces - 1);
        }

        return Color(0.f, 0.f, 0.f);
    }

    return get_bg_color(r);
}
