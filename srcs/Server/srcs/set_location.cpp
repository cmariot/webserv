#include "Server.hpp"

int	Server::set_location(std::vector<std::string> & token_vector, size_t & i)
{
	const size_t	vector_size = token_vector.size();
	size_t			begin = 0;
	size_t			end = 0;
	int				nb_open_braces;
	std::string		uri;

	if (i + 1 >= vector_size || token_vector[i + 1] == "{")
		return (error("Syntax error : No uri for the location block."));
	else if (i + 2 >= vector_size || token_vector[i + 2] != "{")
		return (error("Syntax error : location contexts must have an opening brace after the URI."));
	uri = token_vector[i + 1];
	i += 3;
	begin = i;
	nb_open_braces = 1;
	while (i < vector_size && nb_open_braces != 0)
	{
		end = i;
		if (token_vector[i] == "{")
			++nb_open_braces;
		else if (token_vector[i] == "}")
			--nb_open_braces;
		if (nb_open_braces != 0)
			++i;
		if (nb_open_braces == INT_MAX || nb_open_braces == INT_MIN)
			return (error("int overflow."));
	}
	if (i >= vector_size)
		return (error("Syntax error : unclosed brace in the location block of the configuration file."));
	Location	location(uri);
	std::vector<std::string> tmp_vector(token_vector.begin() + begin, token_vector.begin() + end);
	if (location.parse(tmp_vector))
		return (1);
	if (_locations.find(location.get_uri()) != _locations.end())
		return (error("Syntax error : Multiple Location declarations for the same location uri."));
	_locations.insert(std::pair<std::string, Location>(location.get_uri(), location));
	locations_set = true;
	return (0);
};
