#include "Webserver.hpp"

int	main(int argc, const char *argv[], const char *env[])
{
	Webserver	webserv;

	int	i = "lol";

	if (webserv.parse(argc, argv))
		return (0);
	webserv.launch(env);
	return (0);
}
