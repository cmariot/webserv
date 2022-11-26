#include "Webserver.hpp"

static int	add_to_ready_list(const int & client_socket, const int & epoll_socket)
{
	struct epoll_event	event;

	bzero(&event, sizeof(struct epoll_event));
	event.data.fd = client_socket;
	event.events = EPOLLIN | EPOLLOUT | EPOLLRDHUP;
	if (epoll_ctl(epoll_socket, EPOLL_CTL_ADD, client_socket, &event) == -1)
		return (error(strerror(errno)));
	return (0);
}

static int	set_non_blocking_client(const int & client_socket)
{
	int	flags = fcntl(client_socket, F_GETFL, 0);

	if (flags == -1 || fcntl(client_socket, F_SETFL, flags | O_NONBLOCK) == -1)
		return (error(strerror(errno)));
	return (0);
};

int		Webserver::add_client(void)
{
	const int	client_socket = accept(server.socket,
								(struct sockaddr *)&(server.address),
								(socklen_t *)&(server.addrlen));
	Client		client(client_socket);

	if (client_socket == -1)
		return (error(strerror(errno)));
	if (set_non_blocking_client(client_socket))
		return (1);
	if (add_to_ready_list(client_socket, epoll_socket))
		return (1);
	clients.insert(std::pair<const int, Client>(client_socket, client));
	return (0);
};

bool	Webserver::client_connection(void)
{
	for (size_t	i = 0 ; i <  nb_of_servers ; ++i)
	{
		if (servers[i].socket == event.data.fd)
		{
			print(INFO, "New client connexion");
			server = servers[i];
			return (true);
		}
	}
	return (false);
};
