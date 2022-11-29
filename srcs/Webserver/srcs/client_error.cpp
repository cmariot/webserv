#include "Webserver.hpp"

void	Webserver::remove_client(void)
{
	print(INFO, "Client error : Closing it's connection.");
	clients.erase(event.data.fd);
	epoll_ctl(epoll_socket, EPOLL_CTL_DEL, event.data.fd, NULL);
	close(event.data.fd);
};

bool	Webserver::client_error(void) const
{
	if ((event.events & EPOLLERR) || (event.events & EPOLLHUP))
		return (true);
	return (false);
};
