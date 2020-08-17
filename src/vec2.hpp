#ifndef VEC2_UTIL_H
#define VEC2_UTIL_H

namespace mp
{
    struct vec2
    {
        double x, y;

        vec2(double, double);
        ~vec2();
        
        friend vec2 operator+(const vec2&, const vec2&);
        friend vec2 operator+(const vec2&, double);
        friend vec2 operator+(double, const vec2&);

        vec2 &operator+=(const vec2&);
        vec2 &operator+=(double);

        friend vec2 operator-(const vec2&, const vec2&);
        friend vec2 operator-(const vec2&, double);
        friend vec2 operator-(double, const vec2&);

        vec2 &operator-=(const vec2&);
        vec2 &operator-=(double);

        friend vec2 operator*(const vec2&, const vec2&);
        friend vec2 operator*(const vec2&, double);
        friend vec2 operator*(double, const vec2&);

        vec2 &operator*=(const vec2&);
        vec2 &operator*=(double);

        friend vec2 operator/(const vec2&, const vec2&);
        friend vec2 operator/(const vec2&, double);
        friend vec2 operator/(double, const vec2&);

        vec2 &operator/=(const vec2&);
        vec2 &operator/=(double);

        double dot(const vec2&) const;
        double length() const;
        
        vec2 normalize() const;

        bool operator==(const vec2&);
        bool operator!=(const vec2&);
    };
}

#endif