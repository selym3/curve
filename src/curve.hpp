#ifndef CURVE_UTIL_H
#define CURVE_UTIL_H

#include <vector>
#include <exception>

#include "m_vector.hpp"
#include "m_util.h"

namespace mp
{
    /*
    A curve should represent a way to reach an end point
    from a start point in arbitrary space, where parameter
    t is [0,1]
    */
    template <std::size_t D>
    class curve
    {
    public: // protected:
        std::vector<mp::vec<D>> points;

    public:
        curve() {}
        ~curve() {}

        virtual mp::vec<D> operator()(double t) const = 0;
    };

    /*
    Linearly interpolate between two points.
    */
    template <std::size_t D>
    class line : public curve<D>
    {
    public:
        line(mp::vec<D>&  start, mp::vec<D>& end)
        {
            this->points.push_back(start);
            this->points.push_back(end);
        }

        ~line() {}

        virtual mp::vec<D> operator()(double t) const override
        {
            int index = 0; // (int) t;

            return this->points[index] + ((this->points[index + 1] - this->points[index]) * t);
        }
    };

    /*
    Explicit definition of a quadratic bezier curve, in which you
    interpolate between a start and an auxiliary point and the
    auxiliary and an end point, then interpolate between those points.
    */
    template <std::size_t D>
    class quadratic_bezier : public curve<D>
    {
    public:
        quadratic_bezier(mp::vec<D>& start, mp::vec<D>& to_approach, mp::vec<D>& end)
        {
            this->points.push_back(start);
            this->points.push_back(to_approach);
            this->points.push_back(end);
        }

        ~quadratic_bezier() {}

        virtual mp::vec<D> operator()(double t) const override
        {
            return this->points[1] + (this->points[0] - this->points[1]) * (1 - t) * (1 - t) + (this->points[2] - this->points[1]) * t * t;
        }
    };

    /*
    Explicit definition of a cubic bezier curve in which there are two
    auxilary points that define the path of the curve.
    */
    template <std::size_t D>
    class cubic_bezier : public curve<D>
    {
    public:
        cubic_bezier(mp::vec<D>& start, mp::vec<D>& to_approach, mp::vec<D>& then_approach, mp::vec<D>& end)
        {
            this->points.push_back(start);
            this->points.push_back(to_approach);
            this->points.push_back(then_approach);
            this->points.push_back(end);
        }

        ~cubic_bezier() {}

        virtual mp::vec<D> operator()(double t) const override
        {
            double t1 = (1 - t);
            double t2 = t1 * t1;
            double t3 = t2 * t1;

            double tt = t * t;
            double ttt = tt * t;

            return this->points[0] * t3 + this->points[1] * 3 * t2 * t + this->points[2] * 3 * t1 * tt + this->points[3] * ttt;
        }
    };

    /*
    Illegal argument exception for bezier curve.
    */
    class bezier_exception : public std::exception
    {
        virtual const char *what() const throw()
        {
            return "Number of points provided for a bezier curve must be >= 2";
        }

    public:
        bezier_exception() {}
    };

    /*
    General definition of a bezier curve with n points 
    and (n-2) auxilary points defining the path of the curve.
    There must be at least 2 points.
    */
    template <std::size_t D>
    class bezier : public curve<D>
    {
    private:
        std::size_t size;

    public:
        // Use initializer_list ???
        bezier(const std::vector<mp::vec<D>> &b_points) : size{b_points.size()}
        {
            if (size < 2)
            {
                throw mp::bezier_exception();
            }

            this->points = b_points;
        }

        ~bezier() {}

        virtual mp::vec<D> operator()(double t) const override
        {
            mp::vec<D> out;

            const int n = size - 1;

            const double w = 1 - t;

            double ww = ufpow(w, n);
            double tt = 1;

            for (int i = 0; i <= n; ++i)
            {
                // binomial coefficient
                // (n k) = (n-1 k) + (n-1 k-1) ???
                int b_coeff = nCr(n, i);

                out += (this->points[i] * b_coeff * tt * ww);

                tt *= t;
                ww /= w;
            }

            return out;
        }
    };

    /*
    Utility struct for a pair of vectors
    */
    template <std::size_t D>
    struct pair
    {
        mp::vec<D> first, second;
    };

    /*
    Hermite curve with given start, end, and tangents for each.
    The curve can either be created by explicitly giving each point,
    or giving pairs of points where the second point is the tangent relative
    to the given point.
    */
    template <std::size_t D>
    class hermite : public curve<D>
    {
    public:
        hermite(mp::vec<D>& start, mp::vec<D>& start_tangent, mp::vec<D>& end, mp::vec<D>& end_tangent)
        {
            this->points.push_back(start);
            this->points.push_back(start_tangent);
            this->points.push_back(end);
            this->points.push_back(end_tangent);
        }
        hermite(pair<D> start_point, pair<D> end_point) : hermite(start_point.first, start_point.first + start_point.second, end_point.first, end_point.first + end_point.second)
        {
        }

        ~hermite() {}

        virtual mp::vec<D> operator()(double t) const override
        {
            double tt = t * t;
            double ttt = tt * t;

            mp::vec<D> &start = this->points[0];
            mp::vec<D> &tan1 = this->points[1] - start;
            mp::vec<D> &end = this->points[2];
            mp::vec<D> &tan2 = this->points[3] - end;

            return start * (2 * ttt - 3 * tt + 1) + tan1 * (ttt - 2 * tt + t) + end * (-2 * ttt + 3 * tt) + tan2 * (ttt - tt);
        }
    };

    /*
    Catmull-Rom spline that interpolates between two points
    via basis functions and two auxilary points.
    */
    template <std::size_t D>
    class catmull_rom : public curve<D>
    {
    public:
        catmull_rom(mp::vec<D>& control_a, mp::vec<D>& start, mp::vec<D>& end, mp::vec<D>& control_b)
        {
            this->points.push_back(control_a);
            this->points.push_back(start);
            this->points.push_back(end);
            this->points.push_back(control_b);
        }
        ~catmull_rom() {}

        virtual mp::vec<D> operator()(double t) const override
        {
            double tt = t * t;
            double ttt = tt * t;

            double q1 = -ttt + 2 * tt - t;
            double q2 = 3 * ttt - 5 * tt + 2;
            double q3 = -3 * ttt + 4 * tt + t;
            double q4 = ttt - tt;

            return (this->points[0] * q1 + this->points[1] * q2 + this->points[2] * q3 + this->points[3] * q4) * 0.5;
        }
    };

} // namespace mp

#endif