#include "SoftRayTracer.h"

#include "utils/log.h"
#include "geometry/vector.h"
#include "camera.h"

int main()
{
    init_logger();

    Image  img;

    int    width        = 1280;
    int    height       = 720;
    float  aspect_ratio = float(width) / height;
    bool   status       = create_image(&img, width, height, 3);

    Camera cam(Vec3f(), aspect_ratio, width);

    cam.render(&img);

    write_image(&img, "test_out.tga");

    free_image(&img);

    return 0;
}
