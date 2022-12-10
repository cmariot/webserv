#include "Webserver.hpp"

int Webserver::accept_connexion(int server_socket, struct sockaddr_in server_address, int *client_socket)
{
	int addrlen = sizeof(server_address);

	*client_socket = accept(server_socket, (struct sockaddr *)&server_address, (socklen_t *)&addrlen);
	if (*client_socket == -1)
	{
		error("accept() failed.", NULL);
		perror("accept");
		return (1);
	}
	return (0);
};
