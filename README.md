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
* upgrade curve gui
  * add simple abstraction for different gui implementations (so i can implement with opengl in addition to sdl)
  * when drawing the spline (or calculating the points in general) i could use the length (function not implemented yet) to automatically determine what the t_step needs to be
  * figure out how to do polymorphic lists in order to add multiple curves to gui
* consider adding protection to the list of points that is stored in curve (and then adding iterator methods and special add / remove methods in bezier because it's number of poitns can change and it will still work)
* add method to add control points to bezier class & create driver code that allows full control over bezier curve
* fix cardinal spline (with methods for changing tightness) / figure out how it's related to catmull-rom spline & hermite spline
* add kochanek-bartels spline (with methods for changing tension, bias, continuity)
* create vector with the number of dimensions it's defined in as a template (so that each is a different type) and template some of the curves (the ones that are defined in all dimensions)
