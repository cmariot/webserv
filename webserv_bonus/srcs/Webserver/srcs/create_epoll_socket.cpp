#include "Webserver.hpp"

int	Webserver::create_epoll_socket(int *epoll_socket)
{
	const int	flags = 0;	// Just create an epoll fd

	*epoll_socket = epoll_create1(flags);
	if (*epoll_socket == -1)
	{
		error("epoll_create1() failed.", NULL);
		perror("epoll_create1");
		return (1);
	}
	return (0);
};
