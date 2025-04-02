#pragma once

#include <iostream>

template <typename T>
struct Vec3
{
    T x;
    T y;
    T z;

    Vec3() :
        x(0), y(0), z(0) { }
    Vec3(T i, T j, T k) :
        x(i), y(j), z(k) { }
    inline Vec3<T> operator+(const Vec3<T>& v) const { return Vec3<T>(x + v.x, y + v.y, z + v.z); }
    inline Vec3<T> operator-(const Vec3<T>& v) const { return Vec3<T>(x - v.x, y - v.y, z - v.z); }
    inline Vec3<T> operator*(float c) const { return Vec3<T>(c * x, c * y, c * z); }
    inline Vec3<T> operator/=(float c) const { return Vec3<T>(x / c, y / c, z / c); }
    // dot product
    inline T operator*(const Vec3<T>& vec) const { return x * vec.x + y * vec.y + z * vec.z; }
    // cross product
    inline Vec3<T> operator^(const Vec3<T>& vec)
    {
        return Vec3<T>(
            y * vec.z - z * vec.y,
            z * vec.x - x * vec.z,
            x * vec.y - y * vec.x);
    }
    inline float magnitude() { return std::sqrt(x * x + y * y + z * z); }
    inline float squared_magnitude() { return x * x + y * y + z * z; }
    inline void  normaliize()
    {
        float m = magnitude();
        x       = x / m;
        y       = y / m;
        z       = z / m;
    }

    template <typename>
    friend std::ostream& operator<<(std::ostream& out, const Vec3<T>& v);
};

typedef Vec3<int>   Vec3i;
typedef Vec3<float> Vec3f;

template <typename T>
std::ostream& operator<<(std::ostream& out, const Vec3<T>& v)
{
    out << "(" << v.x << ", " << v.y << ", " << v.z << ")" << std::endl;
    return out;
};

template <typename T>
struct Vec2
{
    T x;
    T y;

    Vec2() :
        x(0), y(0) { }
    Vec2(T i, T j) :
        x(i), y(j) { }
    inline Vec2<T> operator+(const Vec2<T>& v) const { return Vec2<T>(x + v.x, y + v.y); }
    inline Vec2<T> operator-(const Vec2<T>& v) const { return Vec2<T>(x - v.x, y - v.y); }
    // scaler product
    inline Vec2<T> operator*(float c) const { return Vec2<T>(c * x, c * y); }
    inline Vec2<T> operator/=(float c) const { return Vec2<T>(x / c, y / c); }
    // dot product
    inline T operator*(const Vec2<T>& vec) const { return x * vec.x + y * vec.y; }
    // cross product
    inline Vec3<T> operator^(const Vec2<T>& vec) const { return Vec3<T>(0, 0, x * vec.y - y * vec.x); }
    inline float   magnitude() { return std::sqrt(x * x + y * y); }
    inline float   squared_magnitude() { return x * x + y * y; }
    inline void    normaliize()
    {
        float m = magnitude();
        x       = x / m;
        y       = y / m;
    }

    template <typename>
    friend std::ostream& operator<<(std::ostream& out, Vec2<T>& v);
};

typedef Vec2<int>   Vec2i;
typedef Vec2<float> Vec2f;

template <typename T>
std::ostream& operator<<(std::ostream& out, const Vec2<T>& v)
{
    out << "(" << v.x << ", " << v.y << ")" << std::endl;
    return out;
};

template <typename T>
struct Vec4
{
    T x;
    T y;
    T z;
    T w;

    Vec4() :
        x(0), y(0), z(0), w(0) { }
    Vec4(T i, T j, T k, T l) :
        x(i), y(j), z(k), w(l) { }
    inline Vec4<T> operator+(const Vec4<T>& v) const { return Vec4<T>(x + v.x, y + v.y, z + v.z, w + v.w); }
    inline Vec4<T> operator-(const Vec4<T>& v) const { return Vec4<T>(x - v.x, y - v.y, z - v.z, w - v.w); }
    inline Vec4<T> operator*(float c) const { return Vec4<T>(c * x, c * y, c * z, c * w); }
    inline Vec4<T> operator/=(float c) const { return Vec4<T>(x / c, y / c, z / c, w / c); }
    // dot product
    inline T     operator*(const Vec3<T>& vec) const { return x * vec.x + y * vec.y + z * vec.z + w * vec.w; }
    inline float magnitude() { return std::sqrt(x * x + y * y + z * z + w * w); }
    inline float squared_magnitude() { return x * x + y * y + z * z + w * w; }
    inline void  normaliize()
    {
        float m = magnitude();
        x       = x / m;
        y       = y / m;
        z       = z / m;
        w       = w / m;
    }

    template <typename>
    friend std::ostream& operator<<(std::ostream& out, const Vec4<T>& v);
};

typedef Vec4<int>   Vec4i;
typedef Vec4<float> Vec4f;

template <typename T>
std::ostream& operator<<(std::ostream& out, const Vec4<T>& v)
{
    out << "(" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")" << std::endl;
    return out;
};