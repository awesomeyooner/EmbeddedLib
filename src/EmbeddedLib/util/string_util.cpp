#include "EmbeddedLib/util/string_util.hpp"


std::string string_util::add_header(const std::string& header, const std::string& text)
{
    // [ HEADER ]: Hellow World!
    return "[ " + header + " ]: " + text;

} // end of "add_header(const std::string&, const std::string&)"


std::string string_util::timestamped_header(const std::string& header, const std::string& text)
{
    double time = System::get_seconds();
    std::string formatted = "[ " + std::to_string(time) + "] " + add_header(header, text);

    // [ 0.0032331127 ] [ HEADER ]: Hello World!
    return formatted;

} // end of "timestamped_header(const std::string&, const std::string&))"