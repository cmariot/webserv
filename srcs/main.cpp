#include "Webserver.hpp"

int	main(int argc, const char *argv[])
{
	Webserver	webserv;

	if (webserv.parse(argc, argv))
		return (0);
	if (webserv.launch())
		return (0);
	return (0);
}
