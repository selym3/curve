// clang++ vec2.cpp -c -o vec2.o

#include "curve.hpp"

#include <math.h>

mp::vec2::vec2(double x, double y): x(x), y(y) 
{
    // constructor
}

mp::vec2::~vec2()
{
    // deconstructor
}

mp::vec2 mp::operator+(const mp::vec2& lhs, const mp::vec2& rhs)
{
    return mp::vec2(lhs.x + rhs.x, lhs.y + rhs.y);
}

mp::vec2 mp::operator+(const mp::vec2& lhs, double rhs)
{
    return mp::vec2(lhs.x + rhs, lhs.y + rhs);
}

mp::vec2 &mp::vec2::operator+=(const vec2& rhs)
{
    x += rhs.x;
    y += rhs.y;

    return *this;
}

mp::vec2 &mp::vec2::operator+=(double rhs)
{
    x += rhs;
    y += rhs;
    
    return *this;
}

mp::vec2 mp::operator-(const vec2& lhs, const vec2& rhs)
{
    return mp::vec2(lhs.x - rhs.x, lhs.y - rhs.y);
}

mp::vec2 mp::operator-(const vec2& lhs, double rhs)
{
    return mp::vec2(lhs.x - rhs, lhs.y - rhs);
}

mp::vec2 mp::operator-(double lhs, const vec2& rhs)
{
    return mp::vec2(lhs - rhs.x, lhs - rhs.y);
}

mp::vec2 &mp::vec2::operator-=(const vec2& rhs)
{
    this->x -= rhs.x;
    this->y -= rhs.y;

    return *this;
}

mp::vec2 &mp::vec2::operator-=(double rhs)
{
    this->x -= rhs;
    this->y -= rhs;

    return *this;
}

mp::vec2 mp::operator*(const vec2& lhs, const vec2& rhs)
{
    return mp::vec2(lhs.x * rhs.x, lhs.y * rhs.y);
}

mp::vec2 mp::operator*(const vec2& lhs, double rhs)
{
    return mp::vec2(lhs.x * rhs, lhs.y * rhs);
}

mp::vec2 mp::operator*(double lhs, const vec2& rhs)
{
    return mp::vec2(lhs * rhs.x, lhs * rhs.y);
}

mp::vec2 &mp::vec2::operator*=(const vec2& rhs)
{
    this->x *= rhs.x;
    this->y *= rhs.y;

    return *this;
}

mp::vec2 &mp::vec2::operator*=(double rhs)
{
    this->x *= rhs;
    this->y *= rhs;

    return *this;
}

mp::vec2 mp::operator/(const vec2& lhs, const vec2& rhs)
{
    return mp::vec2(lhs.x / rhs.x, lhs.y / rhs.y);
}

mp::vec2 mp::operator/(const vec2& lhs, double rhs)
{
    return mp::vec2(lhs.x / rhs, lhs.y / rhs);
}

mp::vec2 mp::operator/(double lhs, const vec2& rhs)
{
    return mp::vec2(lhs / rhs.x, lhs / rhs.y);
}

mp::vec2 &mp::vec2::operator/=(const vec2& rhs)
{
    this->x /= rhs.x;
    this->y /= rhs.y;

    return *this;
}

mp::vec2 &mp::vec2::operator/=(double rhs)
{
    this->x /= rhs;
    this->y /= rhs;
    
    return *this;
}

double mp::vec2::dot(const vec2& rhs) const
{
    return x * rhs.x + y * rhs.y;
}

double mp::vec2::length() const
{
    return hypot(x, y);
}

mp::vec2 mp::vec2::normalize() const
{
    return *this / length();
}

bool mp::vec2::operator==(const vec2& rhs)
{
    return x == rhs.x && y == rhs.y;
}

bool mp::vec2::operator!=(const vec2& rhs)
{
    return !(*this == rhs);
}