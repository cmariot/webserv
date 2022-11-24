#include "Webserver.hpp"

bool	Webserver::add_to_ready_list(Server & server)
{
	int	addrlen = sizeof(server.address);
	int	ready_socket = accept(server.socket, (struct sockaddr *)&(server.address), (socklen_t *)&addrlen);

	if (ready_socket == -1)
	{
		error("accept() failed.");
		perror("accept");
		return (false);
	}

	int	flags = fcntl(ready_socket, F_GETFL, 0);
	if (fcntl(ready_socket, F_SETFL, flags | O_NONBLOCK) == -1)
		std::cerr << "fcntl" << std::endl;

	struct epoll_event	event;
	bzero(&event, sizeof(struct epoll_event));
	event.data.fd = ready_socket;
	event.events = EPOLLIN | EPOLLOUT;

	if (epoll_ctl(epoll_socket, EPOLL_CTL_ADD, ready_socket, &event) == -1)
	{
		perror("epoll_ctl: ready_socket");
		return (false);
	}
	print(INFO, "Connexion accepted, the client has been add to the interest list.");
	return (true);
};

bool	Webserver::client_connection(void)
{
	for (size_t	i = 0 ; i <  nb_of_servers ; ++i)
		if (server[i].socket == event.data.fd)
			return (add_to_ready_list(server[i]));
	return (false);
};
