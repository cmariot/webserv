#include "Webserver.hpp"

int Webserver::accept_connexion(int *client_socket, Server & server)
{
	int addrlen = sizeof(server.server_address);

	*client_socket = accept(server.server_socket, (struct sockaddr *)&(server.server_address), (socklen_t *)&addrlen);
	if (*client_socket == -1)
	{
		error("accept() failed.", NULL);
		perror("accept");
		return (1);
	}
	return (0);
};
