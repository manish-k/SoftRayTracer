#include "SoftRayTracer.h"

#include "image.h"
#include "utils/log.h"
#include "geometry/vector.h"
#include "geometry/sphere.h"
#include "camera.h"
#include "material.h"

#include <memory>

int main()
{
    init_logger();

    Image  img;

    int    width        = 640;
    int    height       = 360;
    float  aspect_ratio = float(width) / height;
    bool   status       = create_image(&img, width, height, 3);

    Camera cam(Vec3f(), aspect_ratio, width);

    auto   material_ground = std::make_shared<Lambertian>(Color(0.8f, 0.8f, 0.0f));
    auto   material_center = std::make_shared<Lambertian>(Color(0.1f, 0.2f, 0.5f));
    // auto   material_left   = std::make_shared<Metal>(Color(0.8f, 0.8f, 0.8f), 0.3f);
    auto  material_left   = std::make_shared<Dielectric>(1.5f);
    auto  material_bubble = std::make_shared<Dielectric>(1.f / 1.5f);
    auto  material_right  = std::make_shared<Metal>(Color(0.8f, 0.6f, 0.2f), 0.1f);

    World world;
    world.add(std::make_shared<Sphere>(Vec3f(0.f, 0.f, -2.2f), 0.5f, material_center));
    world.add(std::make_shared<Sphere>(Vec3f(-1.f, 0.f, -2.f), 0.5f, material_left));
    world.add(std::make_shared<Sphere>(Vec3f(-1.f, 0.f, -2.f), 0.4f, material_bubble));
    world.add(std::make_shared<Sphere>(Vec3f(1.f, 0.f, -2.f), 0.5f, material_right));
    world.add(std::make_shared<Sphere>(Vec3f(0.f, -100.5f, -2.f), 100.f, material_ground));

    cam.render(&img, world);

    write_image(&img, "test_out.tga");

    free_image(&img);

    return 0;
}
