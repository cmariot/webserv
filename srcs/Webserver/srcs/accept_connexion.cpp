#include "Webserver.hpp"

int Webserver::accept_connexion(int *client_socket, Server & server)
{
	int addrlen = sizeof(server.get_server_address());

	*client_socket = accept(server.get_server_socket(), (struct sockaddr *)&(server._server_address), (socklen_t *)&addrlen);
	if (*client_socket == -1)
	{
		error("accept() failed.", NULL);
		perror("accept");
		return (1);
	}
	return (0);
};
