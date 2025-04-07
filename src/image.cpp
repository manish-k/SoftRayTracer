#include "image.h"
#include "utils/assert.h"
#include "utils/utils.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>
#include <iostream>

bool read_image(Image* img, const char* file_path)
{
    stbi_set_flip_vertically_on_load(true);

    img->data = stbi_load(file_path, &img->width, &img->height, &img->channels, 0);

    if (img->data == nullptr)
    {
        return false;
    }

    img->size       = img->width * img->height * img->channels;
    img->alloc_type = STB_ALLOC;

    return true;
}

bool create_image(Image* img, int width, int height, int channels)
{
    size_t size = width * height * channels;

    img->data = (unsigned char*)calloc(size, 1); // default image with only black color

    if (img->data != nullptr)
    {
        img->width      = width;
        img->height     = height;
        img->channels   = channels;
        img->size       = size;
        img->alloc_type = SELF_ALLOC;

        return true;
    }

    return false;
}

void set_image_pixel_color(Image* img, int x_pos, int y_pos, const Color& color)
{
    ASSERT(img->channels >= 3, "need atleas 3 channels for r,g and b");

    Color          gamma_corrected_color = color.to_gamma();

    unsigned char* pixel = img->data + (y_pos * img->width + x_pos) * img->channels;

    *pixel       = int(256 * clamp(gamma_corrected_color.r, 0.f, .999f)); // red
    *(pixel + 1) = int(256 * clamp(gamma_corrected_color.g, 0.f, .999f)); // green
    *(pixel + 2) = int(256 * clamp(gamma_corrected_color.b, 0.f, .999f)); // green
}

Color get_image_pixel_color(Image* img, int x_pos, int y_pos)
{
    unsigned char* pixel = img->data + (y_pos * img->width + x_pos) * img->channels;
    return Color(float(*(pixel)) / 255, float(*(pixel + 1)) / 255, float(*(pixel + 2)) / 255);
}

void write_image(Image* img, const char* file_path)
{
    stbi_write_tga(file_path, img->width, img->height, img->channels, img->data);
}

void free_image(Image* img)
{
    if (img->alloc_type == SELF_ALLOC && img->data != nullptr)
    {
        free(img->data);
    }
    else if (img->alloc_type == STB_ALLOC && img->data != nullptr)
    {
        stbi_image_free(img->data);
    }

    img->data       = nullptr;
    img->width      = 0;
    img->height     = 0;
    img->channels   = 0;
    img->size       = 0;
    img->alloc_type = NONE_ALLOC;
}
