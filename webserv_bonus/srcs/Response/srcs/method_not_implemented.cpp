#include "Response.hpp"

bool	Response::method_not_implemented(void) const
{
	if (_request.get_method() == "GET")
		return (false);
	if (_request.get_method() == "POST")
		return (false);
	if (_request.get_method() == "DELETE")
		return (false);
	return (true);
};