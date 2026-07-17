#ifndef MATH_UTIL_HPP
#define MATH_UTIL_HPP


#include <cmath>


namespace math
{

    double clamp(double input, double lower_bound, double upper_bound);

    double radians_to_degrees(double radians);

    double degrees_to_radians(double degrees);

} // namespace math

#endif // MATH_UTIL_HPP