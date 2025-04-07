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

    Color                to_gamma() const
    {
        float new_r { 0.f }, new_g { 0.f }, new_b { 0.f };

        if (r > 0) new_r = std::sqrt(r);
        if (g > 0) new_g = std::sqrt(g);
        if (b > 0) new_b = std::sqrt(b);

        return Color(new_r, new_g, new_b);
    }
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