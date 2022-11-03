#include "Location.hpp"

int		Location::parse_upload(std::vector<std::string> & vector, size_t & i)
{
	if (invalid_directive_len(vector, i, ";", 3, 3))
		return (error("Syntax error : invalid upload directive."));
	++i;
	if (vector[i] == "on")
	{
		std::cout << "\t\tupload\t\t\ton;" << std::endl;
		upload = true;
	}
	else if (vector[i] == "off")
	{
		std::cout << "\t\tupload\t\t\toff;" << std::endl;
		upload = false;
	}
	else
		return (error("Syntax error : invalid upload directive."));
	if (vector[++i] != ";")
		return (error("Syntax error : the upload directive doesn't ends by ';'."));
	return (0);
};
