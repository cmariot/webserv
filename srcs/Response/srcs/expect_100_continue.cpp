#include "Response.hpp"

bool    Response::expect_100_continue(void)
{
    const std::multimap<std::string, std::string>::const_iterator   expect
        = _request.get_header().find("Expect");
    
    if (expect != _request.get_header().end())
    {
        if (expect->second == "100-continue")
            return (true);
    }
    return (false);
}