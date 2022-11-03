#include "Location.hpp"

int	Location::parse_directory_file(std::vector<std::string> & vector, size_t & i)
{
	if (invalid_directive_len(vector, i, ";", 3, 3))
		return (error("Syntax error : invalid directory_file directive."));
	directory_file = vector[++i];
	if (vector[++i] != ";")
		return (error("Syntax error : the directory_file directive doesn't ends by ';'."));
	std::cout << "\t\tdirectory_file\t\t" << directory_file << ";" << std::endl;
	return (0);
};
