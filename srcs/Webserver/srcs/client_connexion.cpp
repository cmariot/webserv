#include "Webserver.hpp"

static int	set_non_blocking_client(const int & client_socket)
{
	int	flags = fcntl(client_socket, F_GETFL, 0);

	if (flags == -1 || fcntl(client_socket, F_SETFL, flags | O_NONBLOCK) == -1)
		return (error("fcntl() failed."));
	return (0);
};

static int	add_to_ready_list(const int & client_socket, const int & epoll_socket)
{
	struct epoll_event	event;

	bzero(&event, sizeof(struct epoll_event));
	event.data.fd = client_socket;
	event.events = EPOLLIN | EPOLLOUT;
	if (epoll_ctl(epoll_socket, EPOLL_CTL_ADD, client_socket, &event) == -1)
		return (error("epoll_ctl() failed."));
	return (0);
}

int		Webserver::add_client(void)
{
	const int &	client_socket = accept(_server.socket,
										(struct sockaddr *)&(_server.address),
										(socklen_t *)&(_server.addrlen));
	Client	client(client_socket, _server);

	if (client_socket == -1)
		return (error("accept() failed."));
	if (set_non_blocking_client(client_socket))
		return (1);
	if (add_to_ready_list(client_socket, epoll_socket))
		return (1);
	clients.insert(std::make_pair<const int &, const Client &>(client_socket, client));
	return (0);
};

bool	Webserver::client_connection(void)
{
	for (size_t	i = 0 ; i <  nb_of_servers ; ++i)
	{
		if (servers[i].socket == event.data.fd)
		{
			_server = servers[i];
			return (true);
		}
	}
	return (false);
};
