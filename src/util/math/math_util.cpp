#include "EmbeddedLib/util/math/math_util.hpp"


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