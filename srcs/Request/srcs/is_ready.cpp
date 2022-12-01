#include "Request.hpp"

static bool	header_in_this_request(size_t & i, std::string & _request)
{
	if (i + 1 <= _request.size())
	{
		if (_request[i] == '\r' && _request[i + 1] == '\n')
			return (false);
	}
	return (true);
};

// Un peu de parsing sur la requete pour obtenir les informations qui nous interessent
bool	Request::is_ready(void)
{
	size_t		i = 0;

	if (set_request_line(i))
		return (false);
	if (header_in_this_request(i, _request))
	{
		if (set_header(i))
			return (false);
	}
	if (body_in_this_request())
	{
		if (body_isnot_complete())
			return (false);
	}
	return (true);
};
