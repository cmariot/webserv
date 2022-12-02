#include "Response.hpp"

#define MAX_HEADER_FIELD_SIZE 8192

// check if the uri is too long
bool Response::uri_too_long(void)
{
    if (_request.get_uri().size() > 255)
        return (1);
    return (0);
}

// Check if methods allowed in the location
bool	Response::method_allowed(void)
{

	if (_request.get_method() == "GET" && _location.get_allowed())
		return (0);
	else if (_request.get_method() == "DELETE" && _location.delete_allowed())
		return (0);
	else if (_request.get_method() == "POST" && _location.post_allowed())
		return (0);
	return (1);
}

// check if the method is allowed
static bool	method_implemented(const string &method)
{
	if (method == "GET" || method == "POST" || method == "DELETE")
		return (true);
	return (false);
}

// check the differents headers errors
bool 		Response::headers_check(void)
{
    if (_request.get_header_size() > MAX_HEADER_FIELD_SIZE)
    {
        generate_error_page(431);
        return (1);
    }
    return 0;
}

bool        Response::check_rights(void)
{
    // add check for the rights of the file / directory

    return (0);
}
// check if the request is valid
bool		Response::check_request(void)
{
    if(uri_too_long())
    {
        generate_error_page(414);
        return (true);
    }
	if(get_location() && path_construction())
	{
		generate_error_page(404);
		return (true);
	}
	if(method_implemented(_request.get_method()) == false)
	{
        generate_error_page(501);
    	return (true);
	}
    if(method_allowed() == false)
    {
        generate_error_page(405);
        return (true);
    }
	if (headers_check())
		return (true);

    // if (check_access() == false)
    // {
    //     generate_error_page(403);
    //     return (true);
    // }

	return (false);

}