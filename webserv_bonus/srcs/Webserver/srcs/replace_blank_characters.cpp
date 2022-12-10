#include "Webserver.hpp"

// Replace all the blank characters by spaces
int		Webserver::replace_blank_characters(std::vector<std::string> & string_vector) const
{
	for (size_t i = 0 ; i < string_vector.size() ; ++i)
		for (size_t j = 0 ; j < string_vector[i].size() ; ++j)
			if (isblank(string_vector[i][j]) == true)
				string_vector[i][j] = ' ';
	return (0);
};
