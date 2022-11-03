#include "Location.hpp"

int	Location::parse_allow_methods(std::vector<std::string> & vector, size_t & i)
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
			if (get_method_allowed == false)
				std::cout << "\t\tallow_methods\t\tGET;" << std::endl;
			get_method_allowed = true;
		}
		else if (vector[i] == "POST")
		{
			if (post_method_allowed == false)
				std::cout << "\t\tallow_methods\t\tPOST;" << std::endl;
			post_method_allowed = true;
		}
		else if (vector[i] == "DELETE")
		{
			if (delete_method_allowed == false)
				std::cout << "\t\tallow_methods\t\tDELETE;" << std::endl;
			delete_method_allowed = true;
		}
		else
			return (error("Syntax error : invalid allow_methods directive."));
		++i;
	}
	return (0);
};
