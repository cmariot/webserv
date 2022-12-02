#include "Response.hpp"

// check if the method is allowed
static bool	method_allowed(const string &method)
{
	if (method == "GET" || method == "POST" || method == "DELETE")
		return (true);
	return (false);
}

// check if the uri is too long
bool Response::uri_too_long(void)
{
    if (_request.uri.size() > 255)
        return (0);
    return (1);
}

// check the differents headers errors
bool 		Response::headers_check(void)
{
	cout << _request.get_header().find("Host")->second << endl;
}

// check if the request is valid
bool		Response::check_request(void)
{
	if(get_location() && path_construction())
	{
		generate_error_page(404);
		return (true);
	}
	if(method_allowed(_request.get_method()) == false)
	{
		generate_error_page(405);
		return (true);
	}
	if (headers_check())
	{
		generate_error_page(400);
		return (true);
	}

	return (false);

}