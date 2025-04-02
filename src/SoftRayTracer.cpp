#include "SoftRayTracer.h"
#include "math/vector.h"
#include "color.h"

int main()
{
    Image img;

    int   width  = 256;
    int   height = 256;
    bool  status = create_image(&img, width, height, 3);

    if (status)
    {
        for (int j = 0; j < width; ++j)
        {
            for (int i = 0; i < height; ++i)
            {
                float r = float(i) / (width - 1);
                float g = float(j) / (height - 1);
                float b = 0.0f;

                set_image_pixel_color(&img, i, j, r, g, b);
            }
        }

        write_image(&img, "test_out.tga");
    }

    free_image(&img);

    return 0;
}
