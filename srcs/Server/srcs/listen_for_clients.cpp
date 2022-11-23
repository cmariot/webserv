#include "Server.hpp"

// Listen for client connections on a socket
int Server::listen_for_clients(void) const
{
	const int	backlog = 42;	// Maximum length to which the queue of
								// pending connections may grow

	if (listen(_server_socket, backlog) == -1)
	{
		error("listen() failed.");
		perror("listen");
		return (1);
	}
	return (0);
};