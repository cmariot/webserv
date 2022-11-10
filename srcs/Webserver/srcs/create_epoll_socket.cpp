#include "Webserver.hpp"

int	Webserver::create_main_socket(void)
{
	const int	flags = 0;

	main_socket = epoll_create1(flags);
	if (main_socket == -1)
	{
		error("epoll_create1() failed.", NULL);
		perror("epoll_create1");
		return (1);
	}
	return (0);
};
