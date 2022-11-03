#include "Location.hpp"

int		Location::parse_upload_path(std::vector<std::string> & vector, size_t & i)
{
	if (invalid_directive_len(vector, i, ";", 3, 3))
		return (error("Syntax error : invalid upload_path directive."));
	upload_path = vector[++i];
	if (vector[++i] != ";")
		return (error("Syntax error : the upload_path directive doesn't ends by ';'."));
	std::cout << "\t\tupload_path\t\t" << upload_path << ";" << std::endl;
	return (0);
};
