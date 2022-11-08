#include "Location.hpp"

int		Location::set_upload(std::vector<std::string> & vector, size_t & i)
{
	if (invalid_directive_len(vector, i, ";", 3, 3))
		return (error("Syntax error : invalid upload directive."));
	++i;
	if (vector[i] == "on")
		_upload = true;
	else if (vector[i] == "off")
		_upload = false;
	else
		return (error("Syntax error : invalid upload directive."));
	if (vector[++i] != ";")
		return (error("Syntax error : the upload directive doesn't ends by ';'."));
	return (0);
};
