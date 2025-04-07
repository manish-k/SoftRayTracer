#pragma once

#include <iostream>

struct Color
{
    float r;
    float g;
    float b;
    float a;

    Color() :
        r(0.f), g(0.f), b(0.f), a(0.f) {};
    Color(float red, float green, float blue) :
        r(red), g(green), b(blue), a(1.0f) {};
    Color(float red, float green, float blue, float alpha) :
        r(red), g(green), b(blue), a(alpha) {};

    inline Color operator+(const Color& c) const { return Color(r + c.r, g + c.g, b + c.b); }
    inline Color operator-(const Color& c) const { return Color(r - c.r, g - c.g, b - c.b); }
    inline Color operator*(float c) const { return Color(c * r, c * g, c * b); }
    inline Color operator*(const Color& c) const { return Color(r * c.r, g * c.g, b * c.b); }
    inline Color operator/(float c) const { return Color(r / c, g / c, b / c); }

    // print color
    friend std::ostream& operator<<(std::ostream& out, const Color& c);
};

inline std::ostream& operator<<(std::ostream& out, const Color& c)
{
    out << "(" << int(255.999 * c.r) << ", " << int(255.999 * c.g) << ", " << int(255.999 * c.b) << ")" << std::endl;
    return out;
};

inline Color operator*(float c, const Color& color)
{
    return Color(c * color.r, c * color.g, c * color.b);
}