// clang++ main.cpp vec2.o curve.o -lm -o main
// ./main

#include <iostream>
#include "src/curve.hpp"

// todo: implement second and first derivatives for curve
// todo: implement length of an arc
// Todo: fix hermite spline with tangents

int main()
{

    // mp::line lp({ 0, 0 }, {1, 1});
    // mp::quadratic_bezier lp({0,0}, {0.5,2}, {1,1});
    // mp::cubic_bezier lp({0,0},{0,1},{1,0}, {1,1});
    // mp::catmull_rom lp({0,1}, { 0, 0 } , {1, 1}, {1, 0});
    // mp::hermite lp({10,-10}, {100, 100}, {1,1}, {1 , -1});

    mp::bezier lp ({{0,0}, {0,1}, {1,0}, {1,1}});

    std::cout << "[ ";

    for (auto p : lp.points) 
    {
        std::cout << " ( " << p.x << ", " << p.y << "), ";
    }
    
    std::cout << "]\n";

    std::cout << "[ ";

    const auto t_step = 0.01;

    for (double t = 0; t <= 1 + t_step;t+=t_step)
    {
        mp::vec2 current = lp(t);

        std::cout << "(" << current.x << ", " << current.y << "), ";
    }

    std::cout << "]\n" << std::endl;

    return 0;
}