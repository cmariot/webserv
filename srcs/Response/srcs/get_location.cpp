#include "Response.hpp"

// First check if there is an exact match between the request URI and one of the location URI
// If no exact match found, try to find the best prefix match
// If no match -> 404

int	Response::get_location(void)
{
	std::map<std::string, Location>::const_iterator			ite = _server.get_locations().begin();
	const std::map<std::string, Location>::const_iterator	end = _server.get_locations().end();

	print(INFO, "Selection of the location block for this request.");
	while (ite != end)
	{
		// Check exact match
		if (_request.uri == ite->first)
		{
			_location = ite->second;
			print(INFO, ("An exact match location has been found, using location " + ite->first).c_str());
			return (0);
		}
		++ite;
	}

	size_t	best_match = 0;
	size_t	current_match_len = 0;

	ite = _server.get_locations().begin();
	while (ite != end)
	{
		// Check best prefix match
		if (_request.uri.find(ite->first) == 0)
		{
			current_match_len = ite->first.size();
			if (current_match_len > best_match)
			{
				best_match = current_match_len;
				_location = ite->second;
			}
		}
		++ite;
	}
	if (best_match == 0)
	{
		error("No location block found.");
		return (1);
	}
	print(INFO, ("A partial match location has been found, using location " + _location.get_uri()).c_str());
	return (0);
};
