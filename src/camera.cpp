#include "camera.h"
#include "color.h"

Camera::Camera(Vec3f position, float aspect_ratio, int width)
{
    m_position     = position;
    update(aspect_ratio, width);
}

void Camera::update(float aspect_ratio, int width)
{
    m_image_width  = width;
    m_image_height = int(width / aspect_ratio);

    m_image_height = (m_image_height < 1) ? 1 : m_image_height;

    // TODO: replace focal length calculations with fov angle
    float focal_length = 2.0f;
    float vp_height    = 2.0f;
    float vp_width     = vp_height * float(m_image_width) / m_image_height;

    m_vp_axis_u = Vec3f(vp_width, 0.f, 0.f);
    m_vp_axis_v = Vec3f(0.f, vp_height, 0.f);

    m_vp_pixel_step_u = m_vp_axis_u / m_image_width;
    m_vp_pixel_step_v = m_vp_axis_v / m_image_height;

    m_vp_origin = m_position - Vec3f(0.f, 0.f, focal_length) - m_vp_axis_v / 2 - m_vp_axis_u / 2;
}

void Camera::render(Image* img)
{
    Vec3f vp_start_pixel = m_vp_origin + 0.5 * (m_vp_pixel_step_u + m_vp_pixel_step_v);

    for (int j = 0; j < m_image_height; ++j)
    {
        for (int i = 0; i < m_image_width; ++i)
        {
            Vec3f pixel_center = vp_start_pixel + i * m_vp_pixel_step_u + j * m_vp_pixel_step_v;

            // create ray
            Vec3f ray_direction = pixel_center - m_position;
            Ray   r(m_position, ray_direction);

            // get color
            Color c = get_bg_color(r);
            
            // set color in img
            set_image_pixel_color(img, i, j, c);
        }
    }
}

Color Camera::get_bg_color(const Ray& r)
{
    Vec3f dir = r.direction.unit_vector();

    float y_clamp = 0.5 * (dir.y + 1.0f); // between 0 to 1

    return (1.f - y_clamp) * Color(1.f, 1.f, 1.f) + y_clamp * Color(0.5f, 0.7f, 1.f);
}

