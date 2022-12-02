#include "Webserver.hpp"

int	main(const int argc, const char *argv[], char * const *env)
{
	Webserver	webserv;

	if (webserv.parse(argc, argv, env))
		return (0);
	webserv.launch();
	return (0);
}

┬┴┬┴┤(･_├┬┴┬┴