#include "Response.hpp"

bool Response::has_content(void) const
{
	return (_request.has_body());
};

bool Response::content_too_large(void) const
{
	const double max_size = _server.get_max_size();

	if (max_size != 0)
	{
		if (_request.get_request().size() - _request.get_header_size() >= max_size)
			return (true);
	}
	return (false);	
}
