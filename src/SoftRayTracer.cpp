#include "SoftRayTracer.h"

#include "image.h"
#include "utils/log.h"
#include "geometry/vector.h"
#include "geometry/sphere.h"
#include "camera.h"
#include "material.h"
#include "math/tmath.h"

#include <memory>

void create_scene(World& world)
{
    uint32_t seed            = 3241234;
    auto     ground_material = std::make_shared<Lambertian>(Color(0.5, 0.5, 0.5));
    world.add(std::make_shared<Sphere>(Vec3f(0.f, -1000.f, 0.f), 1000.f, ground_material));

    for (int a = -3; a < 3; a++)
    {
        for (int b = -3; b < 3; b++)
        {
            auto  choose_mat = rand_float(seed);
            Vec3f center(a + 0.9 * rand_float(seed), 0.2, b + 0.9 * rand_float(seed));

            if ((center - Vec3f(4.f, 0.2f, 0.f)).magnitude() > 0.9f)
            {
                std::shared_ptr<Material> sphere_material;

                if (choose_mat < 0.8)
                {
                    // diffuse
                    auto albedo     = rand_color(seed) * rand_color(seed);
                    sphere_material = std::make_shared<Lambertian>(albedo);
                    world.add(std::make_shared<Sphere>(center, 0.2, sphere_material));
                }
                else if (choose_mat < 0.95)
                {
                    // metal
                    auto albedo     = rand_color(seed, 0.5f, 1.f);
                    auto fuzz       = rand_float(seed, 0.f, .5f);
                    sphere_material = std::make_shared<Metal>(albedo, fuzz);
                    world.add(std::make_shared<Sphere>(center, 0.2, sphere_material));
                }
                else
                {
                    // glass
                    sphere_material = std::make_shared<Dielectric>(1.5);
                    world.add(std::make_shared<Sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }

    auto material1 = std::make_shared<Dielectric>(1.5);
    world.add(std::make_shared<Sphere>(Vec3f(0, 1, 0), 1.0, material1));

    auto material2 = std::make_shared<Lambertian>(Color(0.4, 0.2, 0.1));
    world.add(std::make_shared<Sphere>(Vec3f(-4, 1, 0), 1.0, material2));

    auto material3 = std::make_shared<Metal>(Color(0.7, 0.6, 0.5), 0.0);
    world.add(std::make_shared<Sphere>(Vec3f(4, 1, 0), 1.0, material3));
}

int main()
{
    init_logger();

    Image  img;

    int    width        = 640;
    int    height       = 360;
    float  aspect_ratio = float(width) / height;
    bool   status       = create_image(&img, width, height, 3);

    Camera cam(Vec3f(), aspect_ratio, 20.f, width);

    cam.set_view_target(Vec3f(13.f, 2.f, 3.f), Vec3f(0.f, 0.f, 0.f), Vec3f(0.f, 1.f, 0.f));
    World world;

    /*auto  material_ground = std::make_shared<Lambertian>(Color(0.8f, 0.8f, 0.0f));
    auto  material_center = std::make_shared<Lambertian>(Color(0.1f, 0.2f, 0.5f));
    auto  material_left   = std::make_shared<Dielectric>(1.5f);
    auto  material_bubble = std::make_shared<Dielectric>(1.f / 1.5f);
    auto  material_right  = std::make_shared<Metal>(Color(0.8f, 0.6f, 0.2f), 1.f);

    world.add(std::make_shared<Sphere>(Vec3f(0.f, 0.f, -1.2f), 0.5f, material_center));
    world.add(std::make_shared<Sphere>(Vec3f(-1.f, 0.f, -1.f), 0.5f, material_left));
    world.add(std::make_shared<Sphere>(Vec3f(-1.f, 0.f, -1.f), 0.4f, material_bubble));
    world.add(std::make_shared<Sphere>(Vec3f(1.f, 0.f, -1.f), 0.5f, material_right));
    world.add(std::make_shared<Sphere>(Vec3f(0.f, -100.5f, -1.f), 100.f, material_ground));*/

    create_scene(world);

    cam.render(&img, world);

    write_image(&img, "test_out.tga");

    free_image(&img);

    return 0;
}
