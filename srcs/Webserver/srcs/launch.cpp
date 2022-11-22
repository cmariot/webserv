#include "Webserver.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>
#include <netdb.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <string.h>

# define SIGNAL_CAUGHT 1

static const int	create_socket(void)
{
	struct addrinfo	hints;
	int				socket_fd;

	bzero(&hints, sizeof(struct addrinfo));

	return (socket_fd);
};

int		Webserver::launch(char *const *env)
{
	(void)env;

	// Init sockets
	int	socket_fd;

	socket_fd = create_socket();

	print(INFO, "Webserv is waiting for clients connexion ...");
	catch_signal();
	while (true)
	{
		if (wait_event(events, nb_events) == SIGNAL_CAUGHT)
			break ;
		for (size_t i = 0 ; i < nb_events ; ++i)
		{
		
		}
	}
	exit_webserv();
	return (0);
};
