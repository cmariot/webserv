#include "Webserver.hpp"

int	Webserver::add_client(int & client_socket, struct epoll_event *server_event)
{
	fcntl(client_socket, F_SETFL, O_NONBLOCK);
	server_event->events = EPOLLIN | EPOLLET;
	server_event->data.fd = client_socket;
	server_event->data.ptr = &main_socket; // A CHANGER MAIS C'EST UN TEST !
	if (epoll_ctl(main_socket, EPOLL_CTL_ADD, client_socket, server_event) == -1)
	{
		perror("epoll_ctl: client_socket");
		return (1);
	}
	return (0);
};

int Webserver::accept_connexion(int  & client_socket, Server & server, struct epoll_event *events)
{
	int addrlen = sizeof(server.address);

	client_socket = accept(server.socket, (struct sockaddr *)&(server.address), (socklen_t *)&addrlen);
	if (client_socket == -1)
	{
		error("accept() failed.", NULL);
		perror("accept");
		return (1);
	}
	if (add_client(client_socket, events))
		return (1);
	print(INFO, "Connexion accepted, the client has been add to the interest list.");
	return (0);
};

bool	Webserver::client_connexion(size_t & server_index, struct epoll_event & event)
{
	for (server_index = 0 ; server_index <  nb_of_servers ; ++server_index)
		if (event.data.fd == server[server_index].socket)
			return (true);
	return (false);
};
