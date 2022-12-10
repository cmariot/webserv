#include "Utils.hpp"

bool	only_digit(std::string str)
{
	const size_t	size = str.size();

	if (size == 0)
		return (false);
	for (size_t i = 0 ; i < size ; ++i)
	{
		if (str[i] < '0' || str[i] > '9')
			return (false);
	}
	return (true);
}
