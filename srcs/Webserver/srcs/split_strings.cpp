#include "Webserver.hpp"

// Split the strings with ' ' as delimiters
int	Webserver::split_strings(std::vector<std::string> & string_vector,
								std::vector<std::string> & tokens_vector) const
{
	std::string		token;

	try
	{
		for (size_t i = 0 ; i < string_vector.size() ; ++i)
		{
			if (string_vector[i].empty() == false)
			{
				std::istringstream	iss(string_vector[i]);
				while (std::getline(iss, token, ' '))
					if (token.empty() == false)
						tokens_vector.push_back(token);
			}
		}
	}
	catch (std::ios_base::failure & exception)
	{
		return (error(exception.what(), "(getline in parse)"));
	}
	catch (std::bad_alloc & exception)
	{
		return (error(exception.what(), "(push_back in parse)"));
	}
	return (0);
};
