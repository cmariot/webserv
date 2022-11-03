#include "Location.hpp"

bool	Location::invalid_directive_len(std::vector<std::string> & vector, size_t begin_index, std::string untill,
		size_t min_len, size_t max_len)
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
}

int	Location::parse_root(std::vector<std::string> & vector, size_t & i)
{
	if (invalid_directive_len(vector, i, ";", 3, 3))
		return (error("Syntax error : invalid root directive."));
	root = vector[++i];
	if (vector[++i] != ";")
		return (error("Syntax error : the root directive doesn't ends by ';'."));
	std::cout << "\t\troot\t\t\t" << root << ";" << std::endl;
	return (0);
};
