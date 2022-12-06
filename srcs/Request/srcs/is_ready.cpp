#include "Request.hpp"

// Un peu de parsing sur la requete pour obtenir les informations qui nous interessent
bool	Request::is_ready(void)
{
	size_t		i = 0;

	if (set_request_line(i))
		return (false);
	if (header_in_this_request(i))
	{
		if (set_header(i))
			return (false);
		if (body_in_this_request())
		{
			if (body_is_ready() == false)
				return (false);
		}
	}
	print(INFO, "Request :");
	std::cout << _request << std::endl;
	return (true);
};
