#include "Location.hpp"

int	Location::error(std::string error) const
{
	const char	*red_color	= "\033[1m\033[31m";
	const char	*reset		= "\033[0m";

	std::cerr << red_color << error << reset << std::endl;
	return (1);
}

int	Location::error(std::string error, std::string complement) const
{
	const char	*red_color	= "\033[1m\033[31m";
	const char	*reset		= "\033[0m";

	std::cerr << red_color << error << " " << complement << reset << std::endl;
	return (1);
}
