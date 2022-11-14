#include "Response.hpp"

int	Response::get_location(void)
{
	std::map<std::string, Location>::const_iterator	location;

	print(INFO, "Selection of the location block for this request.");
	location = _server.get_locations().begin();
	while (location != _server.get_locations().end())
	{
		std::cout << location->first << std::endl;
		++location;
	}
	return (0);
};
