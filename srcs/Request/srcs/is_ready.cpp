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
			if (set_body())
				return (false);
		}
	}
	if (body_in_this_request())
	{
		// cout << endl << "ON EST LA  ??? " << endl;
		if (body_isnot_complete())
			return (false);
		// cout << endl << "ON EST LA  ??? " << endl;

	}
	return (true);
};
