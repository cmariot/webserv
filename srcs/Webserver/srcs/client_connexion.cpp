#include "Webserver.hpp"

bool	Webserver::accept_connection(Server & server)
{
	int	addrlen = sizeof(server.address);
	int	ready_socket = accept(server.socket, (struct sockaddr *)&(server.address), (socklen_t *)&addrlen);

	if (ready_socket == -1)
	{
		error("accept() failed.");
		perror("accept");
		return (false);
	}

	struct epoll_event	event;
	bzero(&event, sizeof(struct epoll_event));
	event.data.fd = ready_socket;
	event.events = EPOLLIN | EPOLLOUT | EPOLLET | EPOLLRDHUP;

	int	flags = fcntl(ready_socket, F_GETFL, 0);
	if (fcntl(ready_socket, F_SETFL, flags|O_NONBLOCK) == -1)
		std::cerr << "fcntl" << std::endl;

	if (epoll_ctl(epoll_socket, EPOLL_CTL_ADD, ready_socket, &event) == -1)
	{
		perror("epoll_ctl: ready_socket");
		return (false);
	}
	print(INFO, "Connexion accepted, the client has been add to the interest list.");
	return (true);
};

bool	Webserver::client_connection(struct epoll_event & event)
{
	for (size_t	i = 0 ; i <  nb_of_servers ; ++i)
		if (server[i].socket == event.data.fd)
			if (accept_connection(server[i]))
				return (true);
	return (false);
};
