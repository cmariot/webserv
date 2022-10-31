#include "Server.hpp"

int	Server::parse_index_directive(std::vector<std::string> & token_vector, size_t & i)
{
	size_t	j = i;

	if (no_semicolon(token_vector, j))
		return (error("Syntax error : the error_page directive doesn't ends with the ';' character."));
	else if (invalid_directive_len(token_vector, i, ";", 3, token_vector.size()))
		return (error("Syntax error : invalid index directive len."));
	++i;
	while (i != token_vector.size() - 1)
		index.push_back(token_vector[i++]);

	// Affichage ok tant qu'une seule declaration index dans le server,
	// Sinon il y aura des repetitions
	std::cout << "\tindex\t\t\t";
	for (j = 0 ; j < index.size() ; ++j)
	{
		if (j != index.size() - 1)
			std::cout << index[j] << " ";
		else
			std::cout << index[j];
	}
	std::cout << ";" << std::endl;

	return (0);
};
