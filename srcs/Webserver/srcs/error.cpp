#include "Webserver.hpp"

// Display an error and an optional complement
int	Webserver::error(const char *error, const char *complement) const
{
	const char	*red_color	= "\033[1m\033[31m";
	const char	*reset		= "\033[0m";

	std::cerr << red_color << "Error: " << error;
	if (complement != NULL)
		std::cerr << " " << complement;
	std::cerr << reset << std::endl;
	return (1);
};
