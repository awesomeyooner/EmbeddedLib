#include "EmbeddedLib/util/string_formatter.hpp"


using namespace std;


string string_formatter::add_header(const string& header, const string& text)
{
    // [ HEADER ]: Hellow World!
    return "[ " + header + " ]: " + text;

} // end of "add_header(const std::string&, const std::string&)"


string string_formatter::timestamped_header(const string& header, const string& text)
{
    double time = System::get_seconds();
    string formatted = "[ " + to_string(time) + " ] " + add_header(header, text);

    // [ 0.0032331127 ] [ HEADER ]: Hello World!
    return formatted;

} // end of "timestamped_header(const std::string&, const std::string&))"


string string_formatter::to_string(double value, int decimals)
{
    // c-string for snprintf
    char buffer[string_formatter::STRING_BUFFER_SIZE];
    
    // The integer part of the input
    int integer_part = (int)value;

    // The fractional (decimal) part of the input as an integer
    int frac_part = abs((int)((value - integer_part) * pow(10, decimals)));

    // The format command (default to 3 decimals)
    char format_cmd[] = "%d.%03d";
    
    // Set the actual decimal part to the requested amount
    // + '0' makes it the ASCII char, not the actual byte of `decimals`
    format_cmd[5] = decimals + '0';

    // Format with snprintf
    snprintf(buffer, sizeof(buffer), format_cmd, integer_part, frac_part);

    // c-string to normal string
    string converted(buffer);

    return converted;

} // end of "to_string(double, int)"


string string_formatter::to_string(int value)
{
    // c-string for snprintf
    char buffer[string_formatter::STRING_BUFFER_SIZE];
    
    // Format with snprintf
    snprintf(buffer, sizeof(buffer), "%d", value);

    // c-string to normal string
    string converted(buffer);

    return converted;

} // end of "to_string(int)"