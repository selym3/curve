#ifndef CURVE_UTIL_H
#define CURVE_UTIL_H

#include <vector>

// #include <utility>

namespace mp
{

    struct vec2
    {
        double x, y;

        vec2(double, double);
        ~vec2();
        
        vec2 operator+(vec2) const;
        vec2 operator+(double) const;
        vec2 &operator+=(vec2);
        vec2 &operator+=(double);

        vec2 operator-(vec2) const;
        vec2 operator-(double) const;
        vec2 &operator-=(vec2);
        vec2 &operator-=(double);

        vec2 operator*(vec2) const;
        vec2 operator*(double) const;
        vec2 &operator*=(vec2);
        vec2 &operator*=(double);

        vec2 operator/(vec2) const;
        vec2 operator/(double) const;
        vec2 &operator/=(vec2);
        vec2 &operator/=(double);

        double dot(vec2) const;
        double length() const;
        
        vec2 normalize() const;
    };
    
    class curve
    {
        public: // protected:
            std::vector<vec2> points;

        public:
            curve();
            ~curve();

            virtual vec2 operator[](double t) = 0;
    };
    

    class lerp : public curve
    {
        public:
            lerp(vec2, vec2);
            ~lerp();

            virtual vec2 operator[](double t) override;

    };

    class quadratic_bezier : public curve
    {
        public:
            quadratic_bezier(vec2, vec2, vec2);
            ~quadratic_bezier();

            virtual vec2 operator[](double t) override;
            
    };

    class cubic_bezier : public curve
    {
        public:
            cubic_bezier(vec2, vec2, vec2, vec2);
            ~cubic_bezier();

            virtual vec2 operator[](double t) override;
    };

    
    class catmull_rom : public curve
    {
        public:
            catmull_rom(vec2, vec2, vec2, vec2);
            ~catmull_rom();

            virtual vec2 operator[](double t) override;
    };

    class hermite : public curve
    {
        public:
            hermite(vec2, vec2, vec2, vec2);
            ~hermite();

            virtual vec2 operator[](double t) override;
    };
}

#endif