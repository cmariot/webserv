#include "Response.hpp"

int	Response::get_location(void)
{
	std::map<std::string, Location>::const_iterator	location;

	print(INFO, "Selection of the location block for this request.");
	location = _server.get_locations().begin();
	while (location != _server.get_locations().end())
	{
		if (_request.uri.find(location->first) == 0)
		{
			print(INFO, "The location block corresponding to the request has been found.");
			_location = location->second;
			return (0);
		}
		++location;
	}
	error("No location block found.");
	return (1);
};
