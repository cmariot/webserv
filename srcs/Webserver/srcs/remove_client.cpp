#include "Webserver.hpp"

int	Webserver::remove_client(int epoll_socket, int client_socket, struct epoll_event *server_event)
{
	epoll_ctl(epoll_socket, EPOLL_CTL_DEL, client_socket, server_event);
	close(client_socket);
	return (0);
};
