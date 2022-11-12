#include "Location.hpp"

int	Location::set_directory_file(std::vector<std::string> & vector, size_t & i)
{
	if (directory_file_set == true)
		return (error("Syntax error : Multiple directory_file directives."));
	if (invalid_directive_len(vector, i, ";", 3, 3))
		return (error("Syntax error : invalid directory_file directive."));
	_directory_file = vector[++i];
	if (vector[++i] != ";")
		return (error("Syntax error : the directory_file directive doesn't ends by ';'."));
	directory_file_set = true;
	return (0);
};
