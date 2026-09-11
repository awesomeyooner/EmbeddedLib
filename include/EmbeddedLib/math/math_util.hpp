#ifndef MATH_UTIL_HPP
#define MATH_UTIL_HPP


#include <cmath>


namespace math
{

    double clamp(double input, double lower_bound, double upper_bound);

    /**
     * @brief Get the input voltage applied to a resistor divider, given the output voltage
     * 
     * `Vin` -> `R1` -> `R2` -> `GND`
     * 
     * Where `Vout` is the voltage across `R2` and `GND`
     * 
     * @param Vout `double` The output voltage of the R divider
     * @param R1 `double` The resistance of R1, in ohms
     * @param R2 `double` The resistance of R1, in ohms
     * @return `double` 
     */
    double R_divider(double Vout, double R1, double R2);

    double radians_to_degrees(double radians);

    double degrees_to_radians(double degrees);

} // namespace math

#endif // MATH_UTIL_HPP