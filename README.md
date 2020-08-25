# curve

collection of curve representations in c++

## classes

* vec2
  * internal implementation of a 2D Vector
* curve
  * abstract representation of a curve
  * supports function operator for [0,1]
  * needs length(), first / second derivative
* line
  * linearly interpolate between 2 points
* quadratic_bezier
  * bezier curve with start, end, and one anchor point.
* cubic_bezier
  * bezier curve with start, end, and two anchor points.
* catmull_rom
  * catmull rom spline restricted to a start and end point with two anchor points.
* hermite
  * hermite spline with a start, start tangent, end, and end tangent defined.
* bezier
  * bezier curve compatible with n points (first and last are always start and end)

## TODO

* update curve with length(), first, second derivative() functions
* add cardinal spline (with methods for changing tightness) / figure out how it's related to catmull-rom spline & hermite spline
* add kochanek-bartels spline (with methods for changing tension, bias, continuity)
* use std::initializer_list (and consider varargs for m_vector.hpp)
* potentially add back explicit 2d vector and have template overrides for convenience
* create iterators that returns the point, angle, etc and all information (so it can be looped with object destructuring)