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


int math::sign(double input)
{
    // If greater than 0 (positive)
    if(input > 0)
        return 1;
    // If less than 0 (negatie)
    else if(input < 0)
        return -1;
    else
        return 0;

} // end of "sign(double)"


double math::R_divider(double Vout, double R1, double R2)
{
    return Vout * (R1 + R2) / R2;

} // end of "R_divider(double, double, double)"


double math::radians_to_degrees(double radians)
{
    return radians * (180 / M_PI);

} // end of "radians_to_degrees(double)"


double math::degrees_to_radians(double degrees)
{
    return degrees * (M_PI / 180);
}