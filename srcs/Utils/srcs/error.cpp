#include "Utils.hpp"

int	error(std::string error)
{
	const char	*red_color	= "\033[1m\033[31m";
	const char	*reset		= "\033[0m";

	std::cerr << red_color << "[webserv] (error) " << reset <<  error << std::endl;
	return (1);
}

int	error(std::string error, std::string complement)
{
	const char	*red_color	= "\033[1m\033[31m";
	const char	*reset		= "\033[0m";

	std::cerr << red_color << "[webserv] (error) " << reset << error << " " << complement << std::endl;
	return (1);
}
