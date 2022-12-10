#include "Utils.hpp"

bool	invalid_directive_len(std::vector<std::string> & vector, size_t begin_index, std::string untill, size_t min_len, size_t max_len)
{
	size_t	line_len = 0;

	while (begin_index + line_len < vector.size())
	{
		if (vector[begin_index + line_len]  == untill)
		{
			++line_len;
			break ;
		}
		++line_len;
	}
	if (line_len >= min_len && line_len <= max_len)
		return (false);
	else
		return (true);
};

bool	no_semicolon(std::vector<std::string> & vector, size_t & i)
{
	while (i < vector.size() && vector[i] != ";")
		++i;
	if (i == vector.size())
		return (true);
	--i;
	return (false);
};
