#include "Location.hpp"

int	Location::set_root(std::vector<std::string> & vector, size_t & i)
{
	if (_root_set == true)
		return (error("Syntax error multiple root directives in a Location block."));
	if (invalid_directive_len(vector, i, ";", 3, 3))
		return (error("Syntax error : invalid root directive len."));
	_root = vector[++i];
	if (vector[++i] != ";")
		return (error("Syntax error : the root directive doesn't ends by ';'."));
	_root_set = true;
	return (0);
};
