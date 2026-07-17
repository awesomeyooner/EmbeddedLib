#ifndef STRING_FORMATTER_HPP
#define STRING_FORMATTER_HPP

#include <string>
#include <stdio.h>
#include <cmath>

#include "EmbeddedLib/system.hpp"


namespace string_formatter
{
    // The max buffer size for converting a double to a string
    constexpr int STRING_BUFFER_SIZE = 32;

    /**
     * @brief Add a header to a given piece of text. Output will resemble:
     * 
     * `[ MY HEADER ]: Hello World!`
     * 
     * @param header `const std::string&` The header to add to the text
     * @param text `const std::string&` The main message
     * @return `std::string` The formatted string 
     */
    std::string add_header(const std::string& header, const std::string& text);

    /**
     * @brief Add a timestamp along with a header to a piece of text. Output will resemble:
     * 
     * `[ 123.456 ] [ MY HEADER ]: Hello World!`
     * 
     * @param header `const std::string&` The header to add to the text
     * @param text `const std::string&` The main message
     * @return `std::string` The formatted string 
     */
    std::string timestamped_header(const std::string& header, const std::string& text);
    
    /**
     * @brief Convert a double to a string with the given decimal precision. Uses `snprintf` because
     * `std::to_string` does not work.
     * 
     * @param value `double` The value to convert to string
     * @param decimals `int = 3` The number of decimal places
     * @return `std::string` The number represented as a string 
     */
    std::string to_string(double value, int decimals = 3);   

    /**
     * @brief Convert a int to a string with the given decimal precision. Uses `snprintf` because
     * `std::to_string` does not work. This will not add trailing 0's
     * 
     * @param value `int` The value to convert to string
     * @return `std::string` The number represented as a string 
     */
    std::string to_string(int value);
       
} // namespace string_formatter


#endif // STRING_FORMATTER_HPP