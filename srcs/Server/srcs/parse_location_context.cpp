#include "Server.hpp"

int	Server::parse_location_context(std::vector<std::string> & token_vector, size_t & i)
{
	const size_t	vector_size = token_vector.size();
	size_t			begin = 0;
	size_t			end = 0;
	int				nb_open_braces;
	std::string		uri;

	if (i + 1 >= vector_size || token_vector[i + 1] == "{")
		return (error("Syntax error : No uri for the location block.", NULL));
	else if (i + 2 >= vector_size || token_vector[i + 2] != "{")
		return (error("Syntax error : location contexts must have an opening brace after the URI.", NULL));
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
			return (error("int overflow.", NULL));
	}
	if (i >= vector_size)
		return (error("Syntax error : unclosed brace in the location block of the configuration file.", NULL));
	
	std::cout << "\tlocation " << uri << std::endl << "\t{" << std::endl;
	Location	location(uri);

	std::vector<std::string> tmp_vector(token_vector.begin() + begin, token_vector.begin() + end);
	if (location.parse_location(tmp_vector))
		return (1);
	locations.push_back(location);
	std::cout << "\t}" << std::endl;
	
	return (0);
};
