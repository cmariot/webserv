#include "Response.hpp"

bool	Response::Response::method_not_allowed(void) const
{
	if (_request.get_method() == "GET" && _location.get_allowed())
		return (false);
	else if (_request.get_method() == "POST" && _location.post_allowed())
		return (false);
	else if (_request.get_method() == "DELETE" && _location.delete_allowed())
		return (false);
	return (true);
}
