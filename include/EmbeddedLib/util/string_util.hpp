#ifndef STRING_UTIL_HPP
#define STRING_UTIL_HPP

#include <string>
#include <stdio.h>
#include <cmath>

#include "EmbeddedLib/System.hpp"


namespace string_util
{
    constexpr int STRING_BUFFER_SIZE = 32;

    std::string add_header(const std::string& header, const std::string& text);

    std::string timestamped_header(const std::string& header, const std::string& text);
    
    std::string to_string(double value, int decimals = 3);   
}


#endif // STRING_UTIL_HPP