#include "Webserver.hpp"

int	main(const int argc, const char *argv[], char * const *env)
{
	Webserver	webserv;

	if (webserv.parse(argc, argv, env))
		return (0);
	try
	{
		webserv.launch();
	}
	catch (const std::bad_alloc & exception)
	{
		return (error(exception.what(), " - Allocation failed."));
	}
	return (0);
};
