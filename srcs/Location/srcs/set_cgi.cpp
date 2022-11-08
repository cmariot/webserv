#include "Location.hpp"

int	Location::set_cgi(std::vector<std::string> & vector, size_t & i)
{
	if (invalid_directive_len(vector, i, ";", 3, 3))
		return (error("Syntax error : invalid cgi directive."));
	_cgi = vector[++i];
	if (vector[++i] != ";")
		return (error("Syntax error : the cgi directive doesn't ends by ';'."));
	return (0);
};
