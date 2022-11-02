#include "Server.hpp"

int		Server::parse_upload_path_directive(std::vector<std::string> & token_vector, size_t & i)
{
	if (invalid_directive_len(token_vector, i, ";", 3, 3))
		return (error("Syntax error : invalid upload_path directive."));
	upload_path = token_vector[++i];
	if (token_vector[++i] != ";")
		return (error("Syntax error : the upload_path directive doesn't ends by ';'."));
	std::cout << "\tupload_path\t\t" << upload_path << ";" << std::endl;
	return (0);
};
