#pragma once

#include "color.h"

enum allocation_type
{
    NONE_ALLOC,
    SELF_ALLOC,
    STB_ALLOC
};

struct Image
{
    int                  width;
    int                  height;
    int                  channels;
    size_t               size;
    unsigned char*       data;
    enum allocation_type alloc_type;
};

bool read_image(Image* img, const char* file_path);
bool create_image(Image* img, int width, int height, int channels);
void  set_image_pixel_color(Image* img, int x_pos, int y_pos, float r, float g, float b);
void set_image_pixel_color(Image* img, int x_pos, int y_pos, const Color& color);
Color get_image_pixel_color(Image* img, int x_pos, int y_pos);
void  write_image(Image* img, const char* file_path);
void free_image(Image* img);