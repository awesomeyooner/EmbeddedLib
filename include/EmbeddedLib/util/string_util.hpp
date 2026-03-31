#ifndef STRING_UTIL_HPP
#define STRING_UTIL_HPP

#include <string>

#include "EmbeddedLib/System.hpp"


namespace string_util
{

    std::string add_header(const std::string& header, const std::string& text);

    std::string timestamped_header(const std::string& header, const std::string& text);
    
    
}


#endif // STRING_UTIL_HPP