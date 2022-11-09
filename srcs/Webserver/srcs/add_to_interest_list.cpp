#include "Webserver.hpp"

int	Webserver::add_to_interest_list(Server *server)
{
	struct epoll_event	event;

	bzero(&event, sizeof(event));
	event.data.fd = server->_server_socket;
	event.events = EPOLLIN | EPOLLOUT | EPOLLRDHUP;
	if (epoll_ctl(epoll_socket, EPOLL_CTL_ADD, server->_server_socket, &event) == -1)
	{
		error("epoll_ctl() failed.", NULL);
		perror("epoll_ctl: server_socket");
		return (1);
	}
	return (0);
};
