#include "Location.hpp"

// Questions : Allow multiple cgi ? If yes -> set<std::string> !
// CGI syntax ?

int	Location::set_cgi(std::vector<std::string> & vector, size_t & i)
{
	if (cgi_set == true)
		return (error("Syntax error : Multiples CGI directives in the same location context."));
	if (invalid_directive_len(vector, i, ";", 3, 3))
		return (error("Syntax error : invalid cgi directive."));
	if (vector[++i] != ".php")
		return (error("Syntax error : Unknow cgi value :", vector[i]));
	_cgi = vector[i];
	if (vector[++i] != ";")
		return (error("Syntax error : the cgi directive doesn't ends by ';'."));
	cgi_set = true;
	return (0);
};
