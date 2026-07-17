#include "EmbeddedLib/math/math_util.hpp"


double math::clamp(double input, double lower_bound, double upper_bound)
{
    // if the input is bigger than upper bound, return upper bound
    if(input > upper_bound)
        return upper_bound;

    // If the input is lower than lower bound, return lower bound
    else if(input < lower_bound)
        return lower_bound;

    // If the input is within the lower and upper bounds, return input
    else 
        return input;

} // end of "clamp"


double math::radians_to_degrees(double radians)
{
    return radians * (180 / M_PI);

} // end of "radians_to_degrees(double)"


double math::degrees_to_radians(double degrees)
{
    return degrees * (M_PI / 180);
}