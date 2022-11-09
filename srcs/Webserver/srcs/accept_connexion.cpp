#include "Webserver.hpp"

int	Webserver::add_client(int client_socket, struct epoll_event *server_event)
{
	fcntl(client_socket, F_SETFL, O_NONBLOCK);
	server_event->events = EPOLLIN | EPOLLET;
	server_event->data.fd = client_socket;
	if (epoll_ctl(epoll_socket, EPOLL_CTL_ADD, client_socket, server_event) == -1)
	{
		perror("epoll_ctl: client_socket");
		return (1);
	}
	return (0);
};

int Webserver::accept_connexion(int *client_socket, Server & server, struct epoll_event *events)
{
	int addrlen = sizeof(server.get_server_address());

	*client_socket = accept(server.get_server_socket(), (struct sockaddr *)&(server._server_address), (socklen_t *)&addrlen);
	if (*client_socket == -1)
	{
		error("accept() failed.", NULL);
		perror("accept");
		return (1);
	}
	if (add_client(*client_socket, events))
		return (1);

	std::cout << "A client has just connected to the server "
		<< server.get_address().first
		<< ":"
		<< server.get_address().second
		<< std::endl;

	return (0);
};
