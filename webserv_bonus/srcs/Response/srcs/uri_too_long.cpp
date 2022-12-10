#include "Response.hpp"

bool	Response::uri_too_long(void) const
{
	if (_request.get_uri().size() > 255)
		return (true);
	return (false);
};
