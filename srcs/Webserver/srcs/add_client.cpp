#include "Webserver.hpp"

int	Webserver::add_client(int epoll_socket, int client_socket, struct epoll_event *server_event)
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
