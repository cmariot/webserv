#include "Server.hpp"

int	Server::parse_server_names_directive(std::vector<std::string> & token_vector, size_t & i)
{
	size_t	j = i;

	if (no_semicolon(token_vector, j))
		return (error("Syntax error : the server_names directive doesn't ends with the ';' character."));
	else if (invalid_directive_len(token_vector, i, ";", 3, token_vector.size()))
		return (error("Syntax error : invalid server_names directive len."));
	++i;
	std::cout << "\tserver_names\t\t";
	while (i < token_vector.size() && token_vector[i] != ";")
	{
		if (token_vector[i + 1] != ";")
			std::cout << token_vector[i] << " ";
		else
			std::cout << token_vector[i] << ";" << std::endl;
		server_names.push_back(token_vector[i++]);
	}
	return (0);
};
