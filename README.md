# curve

collection of curve representations in c++

## classes

* m_vector<TYPE, SIZE>
  * internal implementation of an n-dimensional vector
* curve
  * abstract representation of a curve
  * supports function call operator for [0,1] for curve points
  * supports subscript operator for [0,1] for first derivative
  * needs length()
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
  * needs derivative

## TODO

* update curve with length()
* add cardinal spline (with methods for changing tightness) / figure out how it's related to catmull-rom spline & hermite spline
* add kochanek-bartels spline (with methods for changing tension, bias, continuity)
* use std::initializer_list (and consider varargs for m_vector.hpp)
* potentially add back explicit 2d vector and have template overrides for convenience
* add first derivative for bezier class
