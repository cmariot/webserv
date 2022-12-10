#include "Location.hpp"

int	Location::set_cgi(std::vector<std::string> & vector, size_t & i)
{
	size_t	j = i;

	if (no_semicolon(vector, j))
		return (error("Syntax error : the cgi directive doesn't ends with the ';' character."));
	else if (invalid_directive_len(vector, i, ";", 3, vector.size()))
		return (error("Syntax error : invalid cgi directive len."));
	++i;
	while (i < vector.size() && vector[i] != ";")
	{
		for (j = 0 ; j < _cgi_extensions.size() ; ++j)
			if (_cgi_extensions[j] == vector[i])
				return (error("Syntax error : Trying to add the same cgi"));;
		if (vector[i].size() && vector[i][0] != '.')
			return (error("Syntax error : Invalid extension for the cgi directive " + vector[i]));;
		_cgi_extensions.push_back(vector[i++]);
		cout << "cgi" << _cgi_extensions.back() << endl; 
	}
	cgi_set = true;

	return (0);
};
