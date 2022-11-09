#include "Webserver.hpp"

int	main(int argc, const char *argv[], const char *env[])
{
	Webserver	webserv;

	(void)env;
	if (webserv.parse(argc, argv))
		return (0);
	webserv.launch();
	return (0);
}
