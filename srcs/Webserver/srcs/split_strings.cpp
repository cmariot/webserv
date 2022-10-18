#include "Webserver.hpp"

// Split the strings with ' ' as delimiters
int		Webserver::split_strings(std::vector<std::string> & string_vector, std::vector<std::string>	& tokens_vector) const
{
	std::string		token;

	for (size_t i = 0 ; i < string_vector.size() ; ++i)
	{
		std::istringstream	iss(string_vector[i]);
		while (std::getline(iss, token, ' '))
		{
			if (token.empty() == false)
			{
				tokens_vector.push_back(token);
			}
		}
	}
	return (0);
};
