#include "Server.hpp"

int	Server::set_server_names(std::vector<std::string> & vector, size_t & i)
{
	size_t	j = i;

	if (no_semicolon(vector, j))
		return (error("Syntax error : the server_names directive doesn't ends with the ';' character."));
	else if (invalid_directive_len(vector, i, ";", 3, vector.size()))
		return (error("Syntax error : invalid server_names directive len."));
	++i;
	std::cout << "\tserver_names\t\t";
	while (i < vector.size() && vector[i] != ";")
	{
		if (vector[i + 1] != ";")
			std::cout << vector[i] << " ";
		else
			std::cout << vector[i] << ";" << std::endl;
		_server_names.push_back(vector[i++]);
	}
	return (0);
};
