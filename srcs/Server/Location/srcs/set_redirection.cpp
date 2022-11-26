#include "Location.hpp"

static int	invalid_redirection_code(const int & _redirection_code)
{
	if (_redirection_code != 301		// Moved permanently
		&& _redirection_code != 308		// Permanent Redirect
		&& _redirection_code != 302		// Found
		&& _redirection_code != 303		// See other
		&& _redirection_code != 307		// Temporary Redirect
		&& _redirection_code != 300		// Multiple choices
		&& _redirection_code != 304)	// Not modified
		return (1);
	return (0);
};

int	Location::set_redirection(std::vector<std::string> & vector, size_t & i)
{
	size_t	j = 0;
	size_t	result_len = 0;

	if (redirection_set == true)
		return (error("Syntax error : Can't have multiple redirections in a location block"));
	if (invalid_directive_len(vector, i, ";", 4, 4))
		return (error("Syntax error : invalid redirection directive len."));
	++i;
	while (vector[i][j] && vector[i][j] >= '0' && vector[i][j] <= '9')
	{
		_redirection_code = _redirection_code * 10 + vector[i][j++] - '0';
		if (++result_len > 3)
			return (error("Syntax error : Invalid redirection code"));
	}
	if (vector[i][j])
		return (error("Syntax error : Invalid redirection code"));
	if (invalid_redirection_code(_redirection_code))
		return (error("Syntax error : Invalid redirection code"));
	_redirection_path = vector[++i];
	++i;
	redirection_set = true;
	return (0);
};
