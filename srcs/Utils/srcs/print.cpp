#include "Utils.hpp"

void	print(int code, const char *message)
{
	const char	*cyan		= "\033[36;1m";
	const char	*reset		= "\033[0m";
	const char	*red		= "\033[31;1m";

	std::cout << "\r";
	if (code == ERR)
		std::cout << cyan << "[webserv] (info)  " << reset;
	if (code == ERR)
		std::cout << red << "[webserv] (error)  " << reset;
	std::cout << message << std::endl;
	return ;
};

void	print(int code, const char *message, const char *complement)
{
	const char	*cyan		= "\033[36;1m";
	const char	*reset		= "\033[0m";
	const char	*red		= "\033[31;1m";

	std::cout << "\r";
	if (code == INFO)
		std::cout << cyan << "[webserv] (info)  " << reset;
	if (code == ERR)
		std::cout << red << "[webserv] (error)  " << reset;
	std::cout << message << " " << complement << std::endl;
	return ;
};
