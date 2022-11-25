#include "Webserver.hpp"

int		Webserver::add_client(void)
{
	// Accept client
	int	addrlen = sizeof(_client_server.address);
	int	client_socket = accept(_client_server.socket, (struct sockaddr *)&(_client_server.address), (socklen_t *)&addrlen);
	if (client_socket == -1)
		return (error("accept() failed."));

	// Set non blocking
	int	flags = fcntl(client_socket, F_GETFL, 0);
	if (flags == -1 || fcntl(client_socket, F_SETFL, flags | O_NONBLOCK) == -1)
		return (error("fcntl() failed."));

	// Add to the ready_list
	struct epoll_event	event;
	bzero(&event, sizeof(struct epoll_event));
	event.data.fd = client_socket;
	event.events = EPOLLIN | EPOLLOUT;
	if (epoll_ctl(epoll_socket, EPOLL_CTL_ADD, client_socket, &event) == -1)
		return (error("epoll_ctl() failed."));

	// Insert the new client in the map
	Client	client(client_socket, _client_server);
	clients.insert(std::make_pair<int, Client>(client_socket, client));

	return (0);
};

bool	Webserver::client_connection(void)
{
	for (size_t	i = 0 ; i <  nb_of_servers ; ++i)
	{
		if (server[i].socket == event.data.fd)
		{
			_client_server = server[i];
			return (true);
		}
	}
	return (false);
};
