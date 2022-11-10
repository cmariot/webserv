#include "Webserver.hpp"

// Display the webserv usage
int	Webserver::usage(void) const
{
	const char	*red_color	= "\033[1m\033[31m";
	const char	*reset		= "\033[0m";

	std::cerr << red_color
		<< "[webserv] " << reset
		<< "Usage: ./webserv [configuration_file]"
		<< std::endl;
	return (1);
};
