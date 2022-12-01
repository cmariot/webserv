#include "Utils.hpp"

void	print(int code, const char *message)
{
	const char	*cyan		= "\033[36;1m";
	const char	*reset		= "\033[0m";

	std::cout << "\r";
	if (code == INFO)
		std::cout << cyan << "[webserv] (info)  " << reset;
	std::cout << message << std::endl;
	return ;
};

void	print(int code, const char *message, const char *complement)
{
	const char	*cyan		= "\033[36;1m";
	const char	*reset		= "\033[0m";

	std::cout << "\r";
	if (code == INFO)
		std::cout << cyan << "[webserv] (info)  " << reset;
	std::cout << message << " " << complement << std::endl;
	return ;
};
