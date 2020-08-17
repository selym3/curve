# curve

collection of curve representations in c++

## classes

* vec2
  * internal implementation of a 2D Vector
* curve
  * abstract representation of a curve
  * supports function operator for [0,1]
  * needs length(), first / second derivative
* lerp
  * linearly interpolate between 2 points
* quadratic_bezier
  * bezier curve with start, end, and one anchor point.
* cubic_bezier
  * bezier curve with start, end, and two anchor points.
* catmull_rom
  * catmull rom spline restricted to a start and end point with two anchor points.
* hermite
  * hermite spline with a start, start tangent, end, and end_tangent defined.
  * (i cant tell if it's working properly)

## TODO

* update curve with length(), first, second derivative() functions
* upgrade curve gui
  * add simple abstraction for different gui implementations (so i can implement with opengl and sdl)
  * when drawing the spline (or calculating the points in general) i could use the length (function not implemented yet) to automatically determine what the t_step needs to be
  * figure out how to do polymorphic lists in order to add multiple curves to gui
