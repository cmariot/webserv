#include "Location.hpp"

int	Location::set_allow_methods(std::vector<std::string> & vector, size_t & i)
{
	size_t	j = i;

	while (j < vector.size() && vector[j] != ";")
		++j;
	if (j == vector.size() || j - i > 5 || vector[j] != ";")
		return (error("Syntax error : invalid allow_methods directive len."));
	++i;
	while (vector[i] != ";")
	{
		if (vector[i] == "GET")
		{
			if (_get_allowed == true)
				return (error("Syntax error : Multiple allow_methods GET in the same location context."));
			_get_allowed = true;
		}
		else if (vector[i] == "POST")
		{
			cout << "POST allowed ?" << endl;
			if (_post_allowed == true)
				return (error("Syntax error : Multiple allow_methods POST in the same location context."));
			_post_allowed = true;
		}
		else if (vector[i] == "DELETE")
		{
			if (_delete_allowed == true)
				return (error("Syntax error : Multiple allow_methods DELETE in the same location context."));
			_delete_allowed = true;
		}
		else
			return (error("Syntax error : invalid allow_methods directive."));
		++i;
	}
	return (0);
};
