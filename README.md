# curve

collection of curve representations in c++

## classes

* vec2
  * internal implementation of a 2D Vector
* curve
  * abstract representation of a curve
  * supports subscript operator for [0,1]
  * needs length(), first / second derivative
* lerp
  * linearly interpolate between 2 points
* quadratic_bezier
  * bezier curve with one control point
* cubic_bezier
  * bezier curve with two control points
* catmull_rom
  * catmull rom spline between a start and an end point (two control points)
* hermite
  * hermite spline with a start, start tangent, end, and end_tangent defined.
  * (i cant tell if it's working properly)

## TODO

* update curve with length(), first, second derivative() functions
* add gui & control ui
