// clang++ curve.cpp -c -o curve.o

#include "curve.hpp"

mp::curve::curve()
{
    // constructor
}

mp::curve::~curve()
{
    // deconstructor
}

mp::line::line(vec2 a, vec2 b): curve()
{
    points.push_back(a);
    points.push_back(b);
}

mp::line::~line()
{
    // deconstructor
}

mp::vec2 mp::line::operator()(double t) const
{
    int index = (int) t;
    // t -= index;

    return points[index] + ((points[index + 1] - points[index]) * t);
}

mp::quadratic_bezier::quadratic_bezier(vec2 start, vec2 control, vec2 end): curve()
{
    points.push_back(start);
    points.push_back(control);
    points.push_back(end);
}

mp::quadratic_bezier::~quadratic_bezier()
{
    // deconstructor
}

mp::vec2 mp::quadratic_bezier::operator()(double t) const
{
    // from start approach control reach end
    return points[1] + (points[0]-points[1]) * (1-t)*(1-t) + (points[2] - points[1]) * t * t;
}

mp::cubic_bezier::cubic_bezier(vec2 start, vec2 control1, vec2 control2, vec2 end): curve()
{
    points.push_back(start);
    points.push_back(control1);
    points.push_back(control2);
    points.push_back(end);
}

mp::cubic_bezier::~cubic_bezier()
{
    // deconstructor
}

mp::vec2 mp::cubic_bezier::operator()(double t) const
{    
    double t1 = (1-t);
    double t2 = t1 * t1;
    double t3 = t2 * t1;

    double tt = t * t;
    double ttt = tt * t;

    return points[0] * t3 + points[1] * 3 * t2 * t + points[2] * 3 * t1 * tt + points[3] * ttt;
}

mp::catmull_rom::catmull_rom(vec2 control1, vec2 start, vec2 end, vec2 control2): curve()
{
    points.push_back(control1);
    points.push_back(start);
    points.push_back(end);
    points.push_back(control2);
}

mp::catmull_rom::~catmull_rom()
{
    // deconstructor
}

mp::vec2 mp::catmull_rom::operator()(double t) const
{
    double tt = t * t;
    double ttt = tt * t;

    double q1 = -ttt + 2 * tt - t;
    double q2 = 3 * ttt - 5 * tt + 2;
    double q3 = -3 * ttt + 4 * tt + t;
    double q4 = ttt - tt;

    return (points[0] * q1 + points[1] * q2 + points[2] * q3 + points[3] * q4) * 0.5;
}

mp::hermite::hermite(vec2 start, vec2 start_tangent, vec2 end, vec2 end_tangent): curve()
{
    points.push_back(start);
    points.push_back(start_tangent);
    points.push_back(end);
    points.push_back(end_tangent);
}

mp::hermite::hermite(pair start_point, pair end_point): 
hermite(start_point.first, start_point.first + start_point.second, end_point.first, end_point.first + end_point.second)
{
    // constructor
}

mp::hermite::~hermite()
{
    // deconstructor
}

mp::vec2 mp::hermite::operator()(double t) const
{
    double tt = t*t;
    double ttt = tt * t;

    mp::vec2 start = points[0];
    mp::vec2 tan1 = points[1] - start;
    mp::vec2 end = points[2];
    mp::vec2 tan2 = points[3] - end;

    return start * (2 * ttt - 3 * tt + 1) + tan1 * (ttt - 2 * tt + t) + end * (-2 * ttt + 3 * tt) + tan2 * (ttt - tt);
}

// TODO: TEST
#include <assert.h>

#include "m_util.h"

// #include <iostream>

mp::bezier::bezier(const std::vector<vec2> &new_points): curve()
{
    size = new_points.size();

    // come up with a better way to throw this error
    assert(size >= 2);
    
    // how to copy over points
    points = std::move(new_points);
}

mp::bezier::~bezier()
{
    // deconstructor
}

mp::vec2 mp::bezier::operator()(double t) const
{
    mp::vec2 out(0,0);

    const int n = size-1;

    const double w = 1 - t;

    double ww = ufpow(w, n);
    double tt = 1;

    for (int i = 0; i <= n; ++i )
    {
        // binomial coefficient
        // there is a chance i dont have to recalculate this everytime because
        // (n k) = (n-1 k) + (n-1 k-1)
        int b_coeff = nCr(n, i);

        // std::cout << "[" << t << "]p" << i << " * ( " << n << " choose " << i << ")(" << b_coeff <<") * t^" << i << "("<< tt <<") * (1-t)^" << (n-i) << "("<< ww <<")\n";

        out += (points[i] * b_coeff * tt * ww);

        tt *= t;
        ww /= w;
    }

    return out;
}
// TODO END 