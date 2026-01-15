#include "EmbeddedLib/util/status.hpp"

namespace status_utils{


std::string status_to_string(StatusCode status)
{
    std::string output = "";

    switch(status){
        case StatusCode::OK:
            output = "OK";
            break;

        case StatusCode::ERROR:
            output = "ERROR";
            break;

        case StatusCode::FAILED:
            output = "FAILED";
            break;
    }

    return output;

} // end of "status_to_string"


bool statuses_OK(std::vector<StatusCode> statuses)
{
    // Loop through all statuses and return false if one of them isn't OK
    for(StatusCode status : statuses){
        if(status != StatusCode::OK)
            return false;
    }

    // If all of them are OK, return true
    return true;

} // end of "statuses_OK"


} // namespace status_utils