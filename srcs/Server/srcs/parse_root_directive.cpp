#include "Server.hpp"

int		Server::parse_root_directive(std::vector<std::string> & token_vector, size_t & i)
{
	if (invalid_directive_len(token_vector, i, ";", 3, 3))
		return (error("Syntax error : invalid root directive."));
	root = token_vector[++i];
	if (token_vector[++i] != ";")
		return (error("Syntax error : the root directive doesn't ends by ';'."));
	std::cout << "\troot\t\t\t" << root << ";" << std::endl;
	return (0);
};
