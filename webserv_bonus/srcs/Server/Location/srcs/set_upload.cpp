#include "Location.hpp"

int		Location::set_upload(std::vector<std::string> & vector, size_t & i)
{
	if (upload_set == true)
		return (error("Syntax error : multiple upload directives for the same location context."));
	if (invalid_directive_len(vector, i, ";", 3, 3))
		return (error("Syntax error : invalid upload directive len."));
	++i;
	if (vector[i] == "on")
		_upload = true;
	else if (vector[i] == "off")
		_upload = false;
	else
		return (error("Syntax error : invalid upload directive."));
	if (vector[++i] != ";")
		return (error("Syntax error : the upload directive doesn't ends by ';'."));
	upload_set = true;
	return (0);
};
