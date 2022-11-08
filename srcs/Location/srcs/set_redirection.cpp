#include "Location.hpp"

int	Location::set_redirection(std::vector<std::string> & vector, size_t & i)
{
	size_t	j = i;
	size_t	result_len = 0;

	if (_redirection == true)
		return (error("Syntax error : Can't have multiple redirections in a location block"));
	_redirection = true;
	while (j < vector.size() && vector[j] != ";")
		++j;
	if (j == vector.size() || j - i != 3 || vector[j] != ";")
		return (error("Syntax error : invalid redirection directive len."));
	++i;
	j = 0;
	while (vector[i][j] && vector[i][j] >= '0' && vector[i][j] <= '9')
	{
		_redirection_code = _redirection_code * 10 + vector[i][j++] - '0';
		if (++result_len > 3)
			return (error("Syntax error : Invalid redirection code"));
	}
	if (vector[i][j])
		return (error("Syntax error : Invalid redirection code"));
	_redirection_path = vector[++i];
	++i;
	return (0);
};
