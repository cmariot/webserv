#include "Location.hpp"

int	Location::parse_directory_listing(std::vector<std::string> & vector, size_t & i)
{
	if (invalid_directive_len(vector, i, ";", 3, 3))
		return (error("Syntax error : invalid directory_listing directive."));
	++i;
	if (vector[i] == "on")
	{
		std::cout << "\t\tdirectory_listing\ton;" << std::endl;
		directory_listing = true;
	}
	else if (vector[i] == "off")
	{
		std::cout << "\t\tdirectory_listing\toff;" << std::endl;
		directory_listing = false;
	}
	else
		return (error("Syntax error : invalid directory_listing directive."));
	if (vector[++i] != ";")
		return (error("Syntax error : the root directive doesn't ends by ';'."));
	return (0);
};
