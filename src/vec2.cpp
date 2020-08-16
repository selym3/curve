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

mp::vec2 mp::vec2::operator+(vec2 rhs) const
{
    return vec2(
        rhs.x + x, rhs.y + y
    );
}

mp::vec2 mp::vec2::operator+(double rhs) const
{
    return vec2(
        x + rhs, y + rhs
    );
}

mp::vec2 &mp::vec2::operator+=(vec2 rhs)
{

    this->x += rhs.x;
    this->y += rhs.y;

    return *this;
}

mp::vec2 &mp::vec2::operator+=(double rhs)
{
    this->x += rhs;
    this->y += rhs;
    
    return *this;
}

mp::vec2 mp::vec2::operator-(vec2 rhs) const
{
    return vec2(
        x - rhs.x, y - rhs.y
    );
}

mp::vec2 mp::vec2::operator-(double rhs) const
{
    return vec2(x - rhs, y - rhs);
}

mp::vec2 &mp::vec2::operator-=(vec2 rhs)
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

mp::vec2 mp::vec2::operator*(vec2 rhs) const
{
    return vec2(
        x * rhs.x,
        y * rhs.y
    );
}

mp::vec2 mp::vec2::operator*(double rhs) const
{
    return vec2(x * rhs, y * rhs);
}

mp::vec2 &mp::vec2::operator*=(vec2 rhs)
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

mp::vec2 mp::vec2::operator/(vec2 rhs) const
{
    return vec2(
        x / rhs.x,
        y / rhs.y
    );
}

mp::vec2 mp::vec2::operator/(double rhs) const
{
    return vec2(x/rhs, y/rhs);
}

mp::vec2 &mp::vec2::operator/=(vec2 rhs)
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

double mp::vec2::dot(vec2 rhs) const
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