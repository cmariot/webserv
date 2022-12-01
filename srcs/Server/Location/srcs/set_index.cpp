#include "Location.hpp"

int	Location::set_index(std::vector<std::string> & vector, size_t & i)
{
	size_t	j = i;

	if (no_semicolon(vector, j))
		return (error("Syntax error : the index directive doesn't ends with the ';' character."));
	else if (invalid_directive_len(vector, i, ";", 3, vector.size()))
		return (error("Syntax error : invalid index directive len."));
	++i;
	while (i < vector.size() && vector[i] != ";")
	{
		for (j = 0 ; j < _index.size() ; ++j)
			if (_index[j] == vector[i])
				return (error("Syntax error : Trying to add the same index"));;
		_index.push_back(vector[i++]);
	}
	return (0);
};
