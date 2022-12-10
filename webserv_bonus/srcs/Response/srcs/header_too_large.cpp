#include "Response.hpp"

bool	Response::header_too_large(void) const
{
	const int max_header_size = 8192;

	if (_request.get_header().size() > max_header_size)
		return (true);
	return (false);
};
